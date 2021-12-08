#include "tlsfront_app.hpp"
#include "tlsfront_socket.hpp"
#include "tlsfront_session.hpp"


tlsfront_app::tlsfront_app(tlsfront_cfg* cfg
                                    , tlsfront_stats* gstats)
{
    ev_socket::set_sockaddr (&m_app_ctx.m_front_addr
                            , cfg->front_ip.c_str()
                            , htons(cfg->front_port));

    ev_socket::set_sockaddr (&m_app_ctx.m_server_addr
                            , cfg->server_ip.c_str()
                            , htons(cfg->server_port));

    ev_socket::set_sockaddr (&m_app_ctx.m_back_addr
                            , cfg->back_ip.c_str()
                            , 0);

    ev_socket::set_sockaddr (&m_app_ctx.m_stats_addr
                            , cfg->stats_ip.c_str()
                            , htons(cfg->stats_port));

    ev_socket::set_sockaddr (&m_app_ctx.m_monitor_addr
                            , cfg->monitor_ip.c_str()
                            , htons(cfg->monitor_port));

    m_app_ctx.m_sock_opt.rcv_buff_len = 0;
    m_app_ctx.m_sock_opt.snd_buff_len = 0;

    m_app_ctx.m_stats_arr.push_back(&m_stats);
    m_app_ctx.m_stats_arr.push_back(gstats);

    m_init_ok = false;
    m_front_lsocket = nullptr;

    m_grp_ctx.m_s_ssl_ctx = SSL_CTX_new(TLS_server_method());
    if (m_grp_ctx.m_s_ssl_ctx) 
    {
        SSL_CTX_set_min_proto_version (m_grp_ctx.m_s_ssl_ctx
                                        , SSL3_VERSION);

        SSL_CTX_set_max_proto_version (m_grp_ctx.m_s_ssl_ctx
                                        , TLS1_3_VERSION);

        SSL_CTX_set_mode(m_grp_ctx.m_s_ssl_ctx
                            , SSL_MODE_ENABLE_PARTIAL_WRITE);

        SSL_CTX_set_session_cache_mode(m_grp_ctx.m_s_ssl_ctx
                                        , SSL_SESS_CACHE_CLIENT);

        SSL_CTX_set_session_id_context(m_grp_ctx.m_s_ssl_ctx
                                        , (unsigned char*)this
                                        , sizeof(void*));

        SSL_CTX_set1_groups_list(m_grp_ctx.m_s_ssl_ctx
                                    , "P-521:P-384:P-256");

        SSL_CTX_set_dh_auto(m_grp_ctx.m_s_ssl_ctx, 1);

        const char* server_cert 
            = "/configs/cert.pem";

        const char* server_key 
            = "/configs/key.pem";

        std::ifstream f(server_cert);
        std::ostringstream ss;
        std::string str;
        ss << f.rdbuf();
        str = ss.str();

        BIO *bio = NULL;
        BIO *kbio = NULL;
        X509 *cert = NULL;
        bio = BIO_new_mem_buf((char *)str.c_str(), -1);
        cert = PEM_read_bio_X509(bio, NULL, 0, NULL);
        SSL_CTX_use_certificate (m_grp_ctx.m_s_ssl_ctx, cert);

        std::ifstream f2(server_key);
        std::ostringstream ss2;
        std::string str2;
        ss2 << f2.rdbuf();
        str2 = ss2.str();
        kbio = BIO_new_mem_buf(str2.c_str(), -1);
        EVP_PKEY *key = NULL;
        key = PEM_read_bio_PrivateKey(kbio, NULL, 0, NULL);
        SSL_CTX_use_PrivateKey(m_grp_ctx.m_s_ssl_ctx, key);

        BIO_free(bio);
        BIO_free(kbio);
        EVP_PKEY_free(key);
        X509_free(cert);

        m_front_lsocket 
            = (tlsfront_socket*) 
            new_tcp_listen (&m_app_ctx.m_front_addr
                            , 1000
                            , &m_app_ctx.m_stats_arr
                            , &m_app_ctx.m_sock_opt);
        
        m_front_lsocket->m_app_ctx = &m_app_ctx;
        m_front_lsocket->m_grp_ctx = &m_grp_ctx;
    }

    m_grp_ctx.m_c_ssl_ctx = SSL_CTX_new(TLS_client_method());
    if (m_grp_ctx.m_c_ssl_ctx)
    {
        SSL_CTX_set_min_proto_version (m_grp_ctx.m_s_ssl_ctx
                                        , SSL3_VERSION);
        SSL_CTX_set_max_proto_version (m_grp_ctx.m_s_ssl_ctx
                                        , TLS1_3_VERSION);

        SSL_CTX_set_mode(m_grp_ctx.m_s_ssl_ctx
                            , SSL_MODE_ENABLE_PARTIAL_WRITE);

        SSL_CTX_set_session_cache_mode(m_grp_ctx.m_s_ssl_ctx
                                        , SSL_SESS_CACHE_CLIENT);

        SSL_CTX_set_session_id_context(m_grp_ctx.m_s_ssl_ctx
                                        , (unsigned char*)this
                                        , sizeof(void*));

        SSL_CTX_set1_groups_list(m_grp_ctx.m_s_ssl_ctx
                                    , "P-521:P-384:P-256");

        SSL_CTX_set_dh_auto(m_grp_ctx.m_s_ssl_ctx, 1);
    }

    m_app_ctx.m_stats_sock 
        = (tlsfront_socket*) new_udp_client (nullptr
                                            , &m_app_ctx.m_stats_addr
                                            , &m_app_ctx.m_stats_arr);

    m_app_ctx.m_monitor_sock 
        = (tlsfront_socket*) new_udp_client (nullptr
                                            , &m_app_ctx.m_monitor_addr
                                            , &m_app_ctx.m_stats_arr);

    if (m_grp_ctx.m_s_ssl_ctx 
        && m_grp_ctx.m_c_ssl_ctx 
        && m_front_lsocket
        && m_app_ctx.m_stats_sock
        && m_app_ctx.m_monitor_sock)
    {
        m_init_ok = true;
    }
}


tlsfront_app::~tlsfront_app()
{
    if (m_app_ctx.m_stats_sock)
    {
        ev_socket::free_udp_client(m_app_ctx.m_stats_sock);
        m_app_ctx.m_stats_sock = nullptr;
    }

    if (m_app_ctx.m_monitor_sock)
    {
        ev_socket::free_udp_client(m_app_ctx.m_monitor_sock);
        m_app_ctx.m_monitor_sock = nullptr;
    }
  
}


void tlsfront_app::run_iter(bool tick_sec)
{
    tlspack_app::run_iter (tick_sec);

    if (tick_sec)
    {
        m_stats.tick_sec();

        json j;
        m_stats.dump_json (j);

        json k;
        k["podIp"] = getenv ("MY_POD_IP");
        k["tcpConnInitSuccess"] = j["tcpConnInitSuccess"];

        std::string s = k.dump();

        m_app_ctx.m_stats_sock->udp_write(
                    (const char*)s.c_str(), s.length());
    }
}

ev_socket* tlsfront_app::alloc_socket(bool is_udp)
{
    return new tlsfront_socket(is_udp);
}

void tlsfront_app::free_socket(ev_socket* ev_sock)
{
    delete ev_sock;
}
