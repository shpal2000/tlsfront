#include "tlsfront_tcp_session.hpp"

tlsfront_tcp_session::tlsfront_tcp_session()
{
    m_front_socket = nullptr;
    m_back_socket = nullptr;
    m_session_established = false;

    m_back_cwbuff = nullptr;
    m_front_cwbuff = nullptr;

    m_back_crbuff = nullptr;
    m_front_crbuff = nullptr;
}

tlsfront_tcp_session::~tlsfront_tcp_session()
{

}