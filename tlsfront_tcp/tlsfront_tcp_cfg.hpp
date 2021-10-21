
#ifndef __TLSFRONT_TCP_CFG__H
#define __TLSFRONT_TCP_CFG__H

#include "app.hpp"

struct tlsfront_tcp_cfg
{
    std::string front_ip;
    u_short front_port;

    std::string back_ip;
    u_short back_port;

};

#endif