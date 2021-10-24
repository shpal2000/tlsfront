#include "tlsfront_ssl_app.hpp"
#include "tlsfront_ssl_socket.hpp"
#include "tlsfront_ssl_session.hpp"


tlsfront_ssl_app::tlsfront_ssl_app(tlsfront_ssl_cfg* cfg, tlsfront_ssl_stats* gstats)
{
    ev_socket::set_sockaddr (&m_front_addr
                            , cfg->front_ip.c_str()
                            , htons(cfg->front_port));

    ev_socket::set_sockaddr (&m_back_addr
                            , cfg->back_ip.c_str()
                            , htons(cfg->back_port));

    ev_socket::set_sockaddr (&m_local_addr
                            , cfg->front_ip.c_str()
                            , 0);

    m_sock_opt.rcv_buff_len = 0;
    m_sock_opt.snd_buff_len = 0;

    m_stats_arr.push_back(&m_stats);
    m_stats_arr.push_back(gstats);
    
    m_front_lsocket
        = (tlsfront_ssl_socket*) new_tcp_listen (&m_front_addr
                                                , 1000
                                                , &m_stats_arr
                                                , &m_sock_opt);


}


tlsfront_ssl_app::~tlsfront_ssl_app()
{

}


void tlsfront_ssl_app::run_iter(bool tick_sec)
{
    tlspack_app::run_iter (tick_sec);

    if (tick_sec)
    {
        m_stats.tick_sec();
    }
}

ev_socket* tlsfront_ssl_app::alloc_socket()
{
    return new tlsfront_ssl_socket();
}

void tlsfront_ssl_app::free_socket(ev_socket* ev_sock)
{
    delete ev_sock;
}
