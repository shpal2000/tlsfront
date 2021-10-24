#ifndef __TLSFRONT_TCP_SESSION__H
#define __TLSFRONT_TCP_SESSION__H

#include "tlsfront_ssl_app.hpp"

class tlsfront_ssl_socket;

class tlsfront_ssl_session
{
public:

    tlsfront_ssl_session();
    ~tlsfront_ssl_session();
    
public:
    tlsfront_ssl_socket* m_front_socket;
    tlsfront_ssl_socket* m_back_socket;
    bool m_session_established;

    ev_buff* m_back_cwbuff;
    ev_buff* m_front_cwbuff;

    ev_buff* m_back_crbuff;
    ev_buff* m_front_crbuff;
    
    std::queue<ev_buff*> m_back_rbuffs;
    std::queue<ev_buff*> m_front_rbuffs;
};

#endif