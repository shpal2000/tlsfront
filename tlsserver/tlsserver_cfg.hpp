
#ifndef __tlsserver_TCP_CFG__H
#define __tlsserver_TCP_CFG__H

#include "tlspack_app.hpp"

struct tlsserver_cfg
{
    std::string m_app_id;
    
    std::string server_ip;
    u_short server_port;
    int server_ssl;

    std::string stats_ip;
    u_short stats_port;

    int send_recv_len;
};

#endif