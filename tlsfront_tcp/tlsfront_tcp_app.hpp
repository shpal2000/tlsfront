#ifndef __TLSFRONT_TCP_APP__H
#define __TLSFRONT_TCP_APP__H

#include "tlspack_app.hpp"

#include "tlsfront_tcp_cfg.hpp"
#include "tlsfront_tcp_stats.hpp"

class tlsfront_tcp_socket;


class tlsfront_tcp_app : public app
{
public:
    tlsfront_tcp_app(tlsfront_tcp_cfg* cfg, tlsfront_tcp_stats* gstats);

    virtual ~tlsfront_tcp_app();

    void run_iter(bool tick_sec);
    
    ev_socket* alloc_socket();
    
    void free_socket(ev_socket* ev_sock);

private:
    ev_sockaddr m_front_addr;
    ev_sockaddr m_back_addr;
    ev_socket_opt m_sock_opt;
    tlsfront_tcp_stats m_stats;
    std::vector<ev_sockstats*> m_stats_arr;

    tlsfront_tcp_socket* m_front_lsocket;
};
#endif