#include "tlsfront_socket.hpp"
#include "tlsfront_session.hpp"

tlsfront_socket::tlsfront_socket(bool is_udp)
                            : ev_socket (is_udp)
{
    m_session = nullptr;
    m_other_socket = nullptr;
    m_read_buff = nullptr;
    m_ssl_init = false;
    m_app_ctx = nullptr;
    m_grp_ctx = nullptr;
    m_ssl = nullptr;
    m_write_close_marked = false;
}

tlsfront_socket::~tlsfront_socket()
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

bool tlsfront_socket::ssl_server_init()
{
    m_ssl = SSL_new (m_grp_ctx->m_s_ssl_ctx);

    if (m_ssl){      
        set_as_ssl_server (m_ssl);
        m_ssl_init = true;
        return true;
    }
    
    return false;
}

bool tlsfront_socket::ssl_client_init()
{
    m_ssl = SSL_new (m_grp_ctx->m_c_ssl_ctx);

    if (m_ssl){      
        set_as_ssl_client (m_ssl);
        m_ssl_init = true;
        return true;
    }
    
    return false;
}

void tlsfront_socket::set_context_from(tlsfront_socket* from_sock)
{
    this->m_app_ctx = from_sock->m_app_ctx;
    this->m_grp_ctx = from_sock->m_grp_ctx;
}

void tlsfront_socket::set_context_from_parent()
{
    tlsfront_socket* parent_socket 
        = (tlsfront_socket*)this->get_parent();

    set_context_from (parent_socket);
}

void tlsfront_socket::abort_session()
{
    this->abort();
    m_other_socket->abort();
}

void tlsfront_socket::on_establish ()
{
    if (m_session == nullptr)
    {
        set_context_from_parent();
        
        tlsfront_socket* server_socket = this;
        tlsfront_session* new_sess = new tlsfront_session();

        if (new_sess)
        {
            server_socket->m_session = new_sess;
            m_session->m_front_socket = server_socket;

            tlsfront_socket* client_socket 
                = (tlsfront_socket*) 
                m_app->new_tcp_connect (&m_app_ctx->m_back_addr
                                        , &m_app_ctx->m_server_addr
                                        , &m_app_ctx->m_stats_arr
                                        , NULL
                                        , &m_app_ctx->m_sock_opt);
            if (client_socket)
            {
                client_socket->set_context_from(server_socket);

                client_socket->m_session = new_sess;
                m_session->m_back_socket = client_socket;

                server_socket->m_other_socket = client_socket;
                client_socket->m_other_socket = server_socket;

                if (m_grp_ctx->m_s_ssl_ctx && !ssl_server_init()) 
                {
                    abort_session();
                }
            }
            else
            {
                delete new_sess;
                server_socket->abort();
                //stats ???
            }
        }
        else
        {
                server_socket->abort();
                //stats ???
        }
    } 
    else
    {
        inc_tlsfront_stats(tlsfrontSessions);
        
        m_session->m_session_established = true;
        if (m_grp_ctx->m_c_ssl_ctx && !ssl_client_init()) 
        {
            abort_session();
        }
    }
}

void tlsfront_socket::on_write ()
{
    if (!m_write_buff_list.empty())
    {
        ev_buff* w_buff = m_write_buff_list.front();

        write_next_data (w_buff->m_buff
                        , w_buff->m_data_offset
                        , w_buff->m_data_len - w_buff->m_data_offset);
    }
}

void tlsfront_socket::on_wstatus (int bytes_written, int write_status)
{
    if (write_status == WRITE_STATUS_NORMAL)
    {
        ev_buff* w_buff = m_write_buff_list.front();

        m_app_ctx->m_monitor_sock->udp_write(
                                w_buff->m_buff + w_buff->m_data_offset
                                , bytes_written);

        w_buff->m_data_offset += bytes_written;
        if (w_buff->m_data_offset == w_buff->m_data_len)
        {
            m_write_buff_list.pop();
            ev_buff::free_ev_buff(w_buff);

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

void tlsfront_socket::on_read ()
{
    ev_buff* rd_buff = nullptr;

    if (m_udp)
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
        }
    }
    else
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

void tlsfront_socket::on_rstatus (int bytes_read, int read_status)
{
    if (m_udp)
    {
        m_read_buff->m_data_len = bytes_read;
        printf("%s", m_read_buff->m_buff);
        delete m_read_buff;
        m_read_buff = nullptr;
    }
    else
    {
        if (bytes_read == 0)
        {
            if (m_session && m_session->m_session_established)
            {
                if (read_status == READ_STATUS_TCP_CLOSE) 
                {
                    if (m_other_socket->m_write_buff_list.empty())
                    {
                        m_other_socket->write_close();
                    }
                    else
                    {
                        m_other_socket->m_write_close_marked = true;
                    }
                }
                else
                {
                    abort_session ();
                }
            }
            else
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

            ev_buff::free_ev_buff(m_read_buff);
            m_read_buff = nullptr;
        }
        else
        {
            m_read_buff->m_data_len = bytes_read;
            m_other_socket->m_write_buff_list.push(m_read_buff);
            m_read_buff = nullptr;
        }
    }
}

void tlsfront_socket::on_error ()
{
    if (m_other_socket)
    {
        m_other_socket->abort();
    }
}

void tlsfront_socket::on_finish ()
{
    if (m_session)
    {
        if (!m_other_socket->m_session)
        {
            delete m_session;
        }

        m_session = nullptr;
    }
}
