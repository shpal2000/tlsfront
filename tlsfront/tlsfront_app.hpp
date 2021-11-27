#ifndef __TLSFRONT_TCP_APP__H
#define __TLSFRONT_TCP_APP__H

#include "tlspack_app.hpp"

#include "tlsfront_cfg.hpp"
#include "tlsfront_stats.hpp"

class tlsfront_socket;

struct tlsfront_grp_ctx
{
    SSL_CTX* m_s_ssl_ctx;
    SSL_CTX* m_c_ssl_ctx;
};

struct tlsfront_app_ctx
{
    ev_sockaddr m_front_addr;
    ev_sockaddr m_server_addr;
    ev_sockaddr m_back_addr;
    ev_sockaddr m_stats_addr;
    
    ev_socket_opt m_sock_opt;
    
    std::vector<ev_sockstats*> m_stats_arr;
};

class tlsfront_app : public tlspack_app
{
public:
    tlsfront_app(tlsfront_cfg* cfg, tlsfront_stats* gstats);

    virtual ~tlsfront_app();

    void run_iter(bool tick_sec);
    
    ev_socket* alloc_socket(bool is_udp=false);
    
    void free_socket(ev_socket* ev_sock);

    tlsfront_stats m_stats;
    tlsfront_socket* m_front_lsocket;

    tlsfront_app_ctx m_app_ctx;
    tlsfront_grp_ctx m_grp_ctx;

    bool m_init_ok;

    tlsfront_socket* m_stats_sock;
};


#endif