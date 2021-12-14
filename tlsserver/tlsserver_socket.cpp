#include "tlsserver_socket.hpp"

tlsserver_socket::tlsserver_socket(bool is_udp)
                            : ev_socket (is_udp)
{
    m_ssl_init = false;
    m_app_ctx = nullptr;
    m_grp_ctx = nullptr;
    m_ssl = nullptr;
    m_write_close_marked = false;
    m_bytes_read = 0;
    m_bytes_written = 0;
}

tlsserver_socket::~tlsserver_socket()
{
    if (m_ssl)
    {
        SSL_free (m_ssl);
        m_ssl = nullptr;
    }
}

bool tlsserver_socket::ssl_server_init()
{
    m_ssl = SSL_new (m_grp_ctx->m_s_ssl_ctx);

    if (m_ssl){      
        set_as_ssl_server (m_ssl);
        m_ssl_init = true;
        return true;
    }
    
    return false;
}

void tlsserver_socket::set_context_from(tlsserver_socket* from_sock)
{
    this->m_app_ctx = from_sock->m_app_ctx;
    this->m_grp_ctx = from_sock->m_grp_ctx;
}

void tlsserver_socket::set_context_from_parent()
{
    tlsserver_socket* parent_socket 
        = (tlsserver_socket*)this->get_parent();

    set_context_from (parent_socket);
}

void tlsserver_socket::abort_session()
{
    this->abort();
}

void tlsserver_socket::on_establish ()
{
    set_context_from_parent();

    if (m_app_ctx->m_server_ssl)
    {
        if (m_grp_ctx->m_s_ssl_ctx && !ssl_server_init()) 
        {
            abort_session();
        }
    }
}

void tlsserver_socket::on_write ()
{
    if (!m_udp)
    {
        if (m_bytes_written < m_app_ctx->m_send_recv_len)
        {
            int bytes_to_write = m_app_ctx->m_send_recv_len - m_bytes_written;

            if (bytes_to_write > m_app_ctx->m_send_buff_len)
            {
                bytes_to_write = m_app_ctx->m_send_buff_len;
            }

            write_next_data (m_app_ctx->m_send_buff
                            , 0
                            , bytes_to_write);
        }
    }
}

void tlsserver_socket::on_wstatus (int bytes_written, int write_status)
{
    if (!m_udp)
    {
        if (write_status == WRITE_STATUS_NORMAL)
        {
            m_bytes_written += bytes_written;
            add_tlsserver_stats(tlsserverBytesInSec,bytes_written);

            if (m_bytes_written == m_app_ctx->m_send_recv_len)
            {
                this->write_close();
            }
        }
        else
        {
            abort_session ();
        }
    }
}

void tlsserver_socket::on_read ()
{
    if (!m_udp)
    {
        read_next_data (m_app_ctx->m_recv_buff
                        , 0
                        , m_app_ctx->m_recv_buff_len);
    }
}

void tlsserver_socket::on_rstatus (int bytes_read, int read_status)
{
    if (!m_udp)
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
        else
        {
            add_tlsserver_stats(tlsserverBytesInSec,bytes_read);
        }
    }
}

void tlsserver_socket::on_error ()
{

}

void tlsserver_socket::on_finish ()
{
}
