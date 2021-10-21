#ifndef __TLSFRONT_TCP_SESSION__H
#define __TLSFRONT_TCP_SESSION__H

#include "tlsfront_tcp_app.hpp"

class tlsfront_tcp_socket;

class tlsfront_tcp_session
{
public:

    tlsfront_tcp_session();
    ~tlsfront_tcp_session();
    
public:
    tlsfront_tcp_socket* m_server_sock;
    tlsfront_tcp_socket* m_client_sock;
    bool m_session_established;

    ev_buff* m_client_current_wbuff;
    ev_buff* m_server_current_wbuff;

    ev_buff* m_client_current_rbuff;
    ev_buff* m_server_current_rbuff;
    
    std::queue<ev_buff*> m_client_rbuffs;
    std::queue<ev_buff*> m_server_rbuffs;
};

#endif