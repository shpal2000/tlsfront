#include "tlsfront_tcp_socket.hpp"

tlsfront_tcp_socket::tlsfront_tcp_socket()
{
    m_app = nullptr;
    m_session = nullptr;
}

tlsfront_tcp_socket::~tlsfront_tcp_socket()
{
    printf("on_establish");
}

void tlsfront_tcp_socket::on_establish ()
{
    printf("on_establish");
}

void tlsfront_tcp_socket::on_write ()
{
    printf("on_establish");
}

void tlsfront_tcp_socket::on_wstatus (int /*bytes_written*/, int /*write_status*/)
{
    printf("on_establish");
}

void tlsfront_tcp_socket::on_read ()
{
    printf("on_establish");
}

void tlsfront_tcp_socket::on_rstatus (int /*bytes_read*/, int /*read_status*/)
{
    printf("on_establish");
}

void tlsfront_tcp_socket::on_finish ()
{
    printf("on_establish");
}