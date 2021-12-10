#include "tlsclient_socket.hpp"

tlsclient_socket::tlsclient_socket(bool is_udp)
                            : ev_socket (is_udp)
{
    m_read_buff = nullptr;
    m_ssl_init = false;
    m_app_ctx = nullptr;
    m_grp_ctx = nullptr;
    m_ssl = nullptr;
    m_write_close_marked = false;
}

tlsclient_socket::~tlsclient_socket()
{
    if (m_read_buff)
    {
        ev_buff::free_ev_buff(m_read_buff);
        m_read_buff = nullptr;
    }

    while (!m_write_buff_list.empty())
    {
        ev_buff::free_ev_buff(m_write_buff_list.front());
        m_write_buff_list.pop();
    }

    if (m_ssl)
    {
        SSL_free (m_ssl);
        m_ssl = nullptr;
    }
}

bool tlsclient_socket::ssl_client_init()
{
    m_ssl = SSL_new (m_grp_ctx->m_c_ssl_ctx);

    if (m_ssl){      
        set_as_ssl_client (m_ssl);
        m_ssl_init = true;
        return true;
    }
    
    return false;
}

void tlsclient_socket::set_context_from(tlsclient_socket* from_sock)
{
    this->m_app_ctx = from_sock->m_app_ctx;
    this->m_grp_ctx = from_sock->m_grp_ctx;
}

void tlsclient_socket::set_context_from_parent()
{
    tlsclient_socket* parent_socket 
        = (tlsclient_socket*)this->get_parent();

    set_context_from (parent_socket);
}

void tlsclient_socket::abort_session()
{
    this->abort();
}

void tlsclient_socket::on_establish ()
{
    if (m_grp_ctx->m_c_ssl_ctx && !ssl_client_init()) 
    {
        abort_session();
    }
}

void tlsclient_socket::on_write ()
{
    if (!m_udp)
    {
        if (!m_write_buff_list.empty())
        {
            ev_buff* w_buff = m_write_buff_list.front();

            write_next_data (w_buff->m_buff
                            , w_buff->m_data_offset
                            , w_buff->m_data_len - w_buff->m_data_offset);
        }
    }
}

void tlsclient_socket::on_wstatus (int bytes_written, int write_status)
{
    if (!m_udp)
    {
        if (write_status == WRITE_STATUS_NORMAL)
        {
            ev_buff* w_buff = m_write_buff_list.front();

            w_buff->m_data_offset += bytes_written;
            add_tlsclient_stats(tlsclientBytesInSec,bytes_written);

            if (w_buff->m_data_offset == w_buff->m_data_len)
            {
                m_write_buff_list.pop();
                w_buff->m_data_offset = 0;

                if (m_write_buff_list.empty() && m_write_close_marked)
                {
                    this->write_close();
                }
            }
        }
        else
        {
            abort_session ();
        }
    }
}

void tlsclient_socket::on_read ()
{
    ev_buff* rd_buff = nullptr;
    if (!m_udp)
    {
        rd_buff = ev_buff::alloc_ev_buff(20480);
        if (rd_buff)
        {
            m_read_buff = rd_buff;
            m_read_buff->m_data_offset = 0;
            m_read_buff->m_data_len = 0;
            read_next_data (rd_buff->m_buff
                            , m_read_buff->m_data_offset
                            , rd_buff->m_buff_len);
        }
        else
        {
            //todo error handling
            abort_session ();
        }
    }
}

void tlsclient_socket::on_rstatus (int bytes_read, int read_status)
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

            ev_buff::free_ev_buff(m_read_buff);
            m_read_buff = nullptr;
        }
        else
        {
            add_tlsclient_stats(tlsclientBytesInSec,bytes_read);
            m_read_buff->m_data_len = bytes_read;
            m_read_buff = nullptr;
        }
    }
}

void tlsclient_socket::on_error ()
{

}

void tlsclient_socket::on_finish ()
{
}
