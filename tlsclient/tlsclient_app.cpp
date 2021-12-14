#include "tlsclient_app.hpp"
#include "tlsclient_socket.hpp"


tlsclient_app::tlsclient_app(tlsclient_cfg* cfg
                                    , tlsclient_stats* gstats)
{
    m_app_ctx.m_app_id = cfg->m_app_id;
    m_app_ctx.m_server_ssl = cfg->server_ssl;

    m_app_ctx.m_send_recv_len = cfg->send_recv_len;

    m_app_ctx.m_cps = cfg->cps;
    m_app_ctx.m_total_conn_count = cfg->total_conn_count;    
    m_app_ctx.m_max_active_conn_count = cfg->max_active_conn_count;

    m_app_ctx.m_recv_buff_len = 4096;
    m_app_ctx.m_recv_buff 
        = (char*) malloc(m_app_ctx.m_recv_buff_len);

    m_app_ctx.m_send_buff_len = 512;
    m_app_ctx.m_send_buff 
        = (char*) malloc(m_app_ctx.m_send_buff_len);

    memset(m_app_ctx.m_send_buff, 'c', m_app_ctx.m_send_buff_len);

    ev_socket::set_sockaddr (&m_app_ctx.m_server_addr
                            , cfg->server_ip.c_str()
                            , htons(cfg->server_port));


    ev_socket::set_sockaddr (&m_app_ctx.m_stats_addr
                            , cfg->stats_ip.c_str()
                            , htons(cfg->stats_port));

    m_app_ctx.m_sock_opt.rcv_buff_len = 0;
    m_app_ctx.m_sock_opt.snd_buff_len = 0;

    m_app_ctx.m_stats_arr.push_back(&m_stats);
    m_app_ctx.m_stats_arr.push_back(gstats);

    m_init_ok = false;

    m_grp_ctx.m_c_ssl_ctx = SSL_CTX_new(TLS_client_method());
    if (m_grp_ctx.m_c_ssl_ctx)
    {
        SSL_CTX_set_min_proto_version (m_grp_ctx.m_c_ssl_ctx
                                        , SSL3_VERSION);
        SSL_CTX_set_max_proto_version (m_grp_ctx.m_c_ssl_ctx
                                        , TLS1_3_VERSION);

        SSL_CTX_set_mode(m_grp_ctx.m_c_ssl_ctx
                            , SSL_MODE_ENABLE_PARTIAL_WRITE);

        SSL_CTX_set_session_cache_mode(m_grp_ctx.m_c_ssl_ctx
                                        , SSL_SESS_CACHE_CLIENT);

        SSL_CTX_set_session_id_context(m_grp_ctx.m_c_ssl_ctx
                                        , (unsigned char*)this
                                        , sizeof(void*));

        SSL_CTX_set1_groups_list(m_grp_ctx.m_c_ssl_ctx
                                    , "P-521:P-384:P-256");

        SSL_CTX_set_dh_auto(m_grp_ctx.m_c_ssl_ctx, 1);
    }

    m_app_ctx.m_stats_sock 
        = (tlsclient_socket*) new_udp_client (nullptr
                                            , &m_app_ctx.m_stats_addr
                                            , &m_app_ctx.m_stats_arr);

    if (m_grp_ctx.m_c_ssl_ctx 
        && m_app_ctx.m_stats_sock
        && m_app_ctx.m_send_buff
        && m_app_ctx.m_recv_buff)
    {
        m_init_ok = true;
    }

    m_stop = false;
    m_curr_conn_count = 0;
}


tlsclient_app::~tlsclient_app()
{
    if (m_app_ctx.m_stats_sock)
    {
        ev_socket::free_udp_client(m_app_ctx.m_stats_sock);
        m_app_ctx.m_stats_sock = nullptr;
    }  
}


void tlsclient_app::run_iter(bool tick_sec)
{
    tlspack_app::run_iter (tick_sec);

    if (tick_sec)
    {
        m_stats.tick_sec();

        json j;
        m_stats.dump_json (j);

        j["appId"] = m_app_ctx.m_app_id;
        j["podIp"] = getenv ("MY_POD_IP");

        std::string s = j.dump();

        m_app_ctx.m_stats_sock->udp_write(
                    (const char*)s.c_str(), s.length());
    }

    if (to_new_connect())
    {
        tlsclient_socket* client_socket 
            = (tlsclient_socket*) 
            new_tcp_connect (NULL
                            , &m_app_ctx.m_server_addr
                            , &m_app_ctx.m_stats_arr
                            , NULL
                            , &m_app_ctx.m_sock_opt);
        
        if (client_socket)
        {
            m_curr_conn_count++;
            client_socket->m_app_ctx = &m_app_ctx;
            client_socket->m_grp_ctx = &m_grp_ctx;
        }
    }
}

ev_socket* tlsclient_app::alloc_socket(bool is_udp)
{
    return new tlsclient_socket(is_udp);
}

void tlsclient_app::free_socket(ev_socket* ev_sock)
{
    delete ev_sock;
}

bool tlsclient_app::to_new_connect()
{
    bool n = false;

    if (not m_stop) {
        if (m_curr_conn_count == 0){
            m_conn_init_time = std::chrono::steady_clock::now ();
            n = 1;
        } else if ((m_app_ctx.m_total_conn_count == 0) 
                || (m_curr_conn_count < m_app_ctx.m_total_conn_count)){

            if ( (m_app_ctx.m_max_active_conn_count == 0) || (m_stats.tcpConnInitInUse < m_app_ctx.m_max_active_conn_count) )  {
                auto t = std::chrono::steady_clock::now();
                auto span = std::chrono::duration_cast<std::chrono::nanoseconds>
                                                (t - m_conn_init_time).count();
                uint64_t c = (m_app_ctx.m_cps * span) / 1000000000;
                if (c > m_curr_conn_count ) {
                    n = true;
                }
            }
        }
    }

    return n;
}