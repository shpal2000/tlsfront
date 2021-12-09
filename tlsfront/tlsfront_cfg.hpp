
#ifndef __TLSFRONT_TCP_CFG__H
#define __TLSFRONT_TCP_CFG__H

#include "tlspack_app.hpp"

struct tlsfront_cfg
{
    std::string m_app_id;
    
    std::string front_ip;
    u_short front_port;

    std::string back_ip;
    // u_short back_port;

    std::string server_ip;
    u_short server_port;

    std::string stats_ip;
    u_short stats_port;

    std::string monitor_ip;
    u_short monitor_port;

};

#endif