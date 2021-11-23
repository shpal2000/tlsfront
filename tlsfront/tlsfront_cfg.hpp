
#ifndef __TLSFRONT_TCP_CFG__H
#define __TLSFRONT_TCP_CFG__H

#include "tlspack_app.hpp"

struct tlsfront_cfg
{
    std::string front_ip;
    u_short front_port;

    std::string back_ip;
    // u_short back_port;

    std::string server_ip;
    u_short server_port;

};

#endif