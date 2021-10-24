#include "tlsfront_ssl_session.hpp"

tlsfront_ssl_session::tlsfront_ssl_session()
{
    m_front_socket = nullptr;
    m_back_socket = nullptr;
    m_session_established = false;

}

tlsfront_ssl_session::~tlsfront_ssl_session()
{

}