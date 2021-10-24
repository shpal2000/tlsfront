#include "tlsfront_ssl_session.hpp"

tlsfront_ssl_session::tlsfront_ssl_session()
{
    m_front_socket = nullptr;
    m_back_socket = nullptr;
    m_session_established = false;

    m_back_cwbuff = nullptr;
    m_front_cwbuff = nullptr;

    m_back_crbuff = nullptr;
    m_front_crbuff = nullptr;
}

tlsfront_ssl_session::~tlsfront_ssl_session()
{

}