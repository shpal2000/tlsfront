#include "tlsfront_tcp_app.hpp"
#include "tlsfront_tcp_socket.hpp"
#include "tlsfront_tcp_session.hpp"


tlsfront_tcp_app::tlsfront_tcp_app(tlsfront_tcp_cfg* cfg, tlsfront_tcp_stats* gstats)
{
    ev_socket::set_sockaddr (&m_front_addr
                            , cfg->front_ip.c_str()
                            , htons(cfg->front_port));

    ev_socket::set_sockaddr (&m_back_addr
                            , cfg->back_ip.c_str()
                            , htons(cfg->back_port));
    
    m_sock_opt.rcv_buff_len = 0;
    m_sock_opt.snd_buff_len = 0;

    m_stats_arr.push_back(&m_stats);
    m_stats_arr.push_back(gstats);
    
    m_front_lsocket
        = (tlsfront_tcp_socket*) new_tcp_listen (&m_front_addr
                                                , 1000
                                                , &m_stats_arr
                                                , &m_sock_opt);


}

tlsfront_tcp_app::~tlsfront_tcp_app()
{

}

