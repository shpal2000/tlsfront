#include "tlsfront_session.hpp"

tlsfront_session::tlsfront_session()
{
    m_front_socket = nullptr;
    m_back_socket = nullptr;
    m_session_established = false;

}

tlsfront_session::~tlsfront_session()
{

}