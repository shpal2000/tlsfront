#ifndef __TLSFRONT_TCP_SESSION__H
#define __TLSFRONT_TCP_SESSION__H

#include "tlsfront_app.hpp"

class tlsfront_socket;

class tlsfront_session
{
public:

    tlsfront_session();
    ~tlsfront_session();
    
public:
    tlsfront_socket* m_front_socket;
    tlsfront_socket* m_back_socket;
    bool m_session_established;
};

#endif