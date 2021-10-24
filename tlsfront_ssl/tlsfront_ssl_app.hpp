#ifndef __TLSFRONT_TCP_APP__H
#define __TLSFRONT_TCP_APP__H

#include "tlspack_app.hpp"

#include "tlsfront_ssl_cfg.hpp"
#include "tlsfront_ssl_stats.hpp"

class tlsfront_ssl_socket;

struct tlsfront_ssl_grp_ctx
{
    SSL_CTX* m_s_ssl_ctx;
    SSL_CTX* m_c_ssl_ctx;
};

struct tlsfront_ssl_app_ctx
{
    ev_sockaddr m_front_addr;
    ev_sockaddr m_back_addr;
    ev_sockaddr m_local_addr;
    ev_socket_opt m_sock_opt;
    
    std::vector<ev_sockstats*> m_stats_arr;
};

class tlsfront_ssl_app : public tlspack_app
{
public:
    tlsfront_ssl_app(tlsfront_ssl_cfg* cfg, tlsfront_ssl_stats* gstats);

    virtual ~tlsfront_ssl_app();

    void run_iter(bool tick_sec);
    
    ev_socket* alloc_socket();
    
    void free_socket(ev_socket* ev_sock);

    tlsfront_ssl_stats m_stats;
    tlsfront_ssl_socket* m_front_lsocket;

    tlsfront_ssl_app_ctx m_app_ctx;
    tlsfront_ssl_grp_ctx m_grp_ctx;

    bool m_init_ok;
};


#endif