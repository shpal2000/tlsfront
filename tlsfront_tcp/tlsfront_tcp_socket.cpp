#include "tlsfront_tcp_socket.hpp"

tlsfront_tcp_socket::tlsfront_tcp_socket()
{
    m_app = nullptr;
    m_session = nullptr;
};

tlsfront_tcp_socket::~tlsfront_tcp_socket()
{

};

void tlsfront_tcp_socket::on_establish ()
{
}

void tlsfront_tcp_socket::on_write ()
{

}

void tlsfront_tcp_socket::on_wstatus (int /*bytes_written*/, int write_status)
{

}

void tlsfront_tcp_socket::on_read ()
{

}

void tlsfront_tcp_socket::on_rstatus (int bytes_read, int read_status)
{

}

void tlsfront_tcp_socket::on_finish ()
{

}