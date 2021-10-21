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
    ev_buff* rd_buff = new ev_buff(2048);
    if (rd_buff && rd_buff->m_buff)
    {
        read_next_data (rd_buff->m_buff, 0, rd_buff->m_buff_len, true);
    }
    else
    {
        //todo error handling
    }
}

void tlsfront_tcp_socket::on_rstatus (int bytes_read, int read_status)
{
    if (bytes_read == 0)
    {
            if (read_status == READ_STATUS_TCP_CLOSE) 
            {
                this->write_close();
            }
            else
            {
                this->abort();
            }
    }
}

void tlsfront_tcp_socket::on_finish ()
{
    printf("on_establish");
}