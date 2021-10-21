#include "tlsfront_tcp_session.hpp"

tlsfront_tcp_session::tlsfront_tcp_session()
{
    m_server_sock = nullptr;
    m_client_sock = nullptr;
    m_session_established = false;

    m_client_current_wbuff = nullptr;
    m_server_current_wbuff = nullptr;

    m_client_current_rbuff = nullptr;
    m_server_current_rbuff = nullptr;
}

tlsfront_tcp_session::~tlsfront_tcp_session()
{

}