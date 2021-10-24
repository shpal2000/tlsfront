#ifndef __TLSFRONT_TCP_APP__H
#define __TLSFRONT_TCP_APP__H

#include "tlspack_app.hpp"

#include "tlsfront_ssl_cfg.hpp"
#include "tlsfront_ssl_stats.hpp"

class tlsfront_ssl_socket;


class tlsfront_ssl_app : public tlspack_app
{
public:
    tlsfront_ssl_app(tlsfront_ssl_cfg* cfg, tlsfront_ssl_stats* gstats);

    virtual ~tlsfront_ssl_app();

    void run_iter(bool tick_sec);
    
    ev_socket* alloc_socket();
    
    void free_socket(ev_socket* ev_sock);

    ev_sockaddr m_front_addr;
    ev_sockaddr m_back_addr;
    ev_sockaddr m_local_addr;
    ev_socket_opt m_sock_opt;
    tlsfront_ssl_stats m_stats;
    std::vector<ev_sockstats*> m_stats_arr;

    tlsfront_ssl_socket* m_front_lsocket;
};


#endif