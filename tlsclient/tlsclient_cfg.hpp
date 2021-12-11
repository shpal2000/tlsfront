
#ifndef __tlsclient_TCP_CFG__H
#define __tlsclient_TCP_CFG__H

#include "tlspack_app.hpp"

struct tlsclient_cfg
{
    std::string m_app_id;
    
    std::string server_ip;
    u_short server_port;
    int server_ssl;

    std::string stats_ip;
    u_short stats_port;

    int send_recv_len;

    int cps;
    uint64_t total_conn_count;
    uint64_t max_active_conn_count;
};

#endif