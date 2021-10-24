#include "tlsfront_ssl_socket.hpp"
#include "tlsfront_ssl_session.hpp"

tlsfront_ssl_socket::tlsfront_ssl_socket(SSL_CTX* ssl_ctx)
{
    m_session = nullptr;
    m_other_socket = nullptr;
    m_read_buff = nullptr;
    m_write_buff = nullptr;
    m_ssl_init = false;
    m_ssl_ctx = ssl_ctx;
}

tlsfront_ssl_socket::~tlsfront_ssl_socket()
{
    if (m_read_buff)
    {
        ev_buff::free_ev_buff(m_read_buff);
        m_read_buff = nullptr;
    }

    if (m_write_buff)
    {
        ev_buff::free_ev_buff(m_write_buff);
        m_write_buff = nullptr;
    }

    while (!m_write_buff_list.empty())
    {
        ev_buff::free_ev_buff(m_write_buff_list.front());
        m_write_buff_list.pop();
    }
}

bool tlsfront_ssl_socket::ssl_init()
{
    m_ssl = SSL_new (m_ssl_ctx);

    if (m_ssl){      
        set_as_ssl_server (m_ssl);
        m_ssl_init = true;
        return true;
    }
    
    return false;
}

void tlsfront_ssl_socket::on_establish ()
{
    tlsfront_ssl_app* app = (tlsfront_ssl_app*) this->m_app;

    if (m_session == nullptr)
    {
        tlsfront_ssl_socket* server_socket = this;
        tlsfront_ssl_session* new_sess = new tlsfront_ssl_session();

        if (new_sess)
        {
            tlsfront_ssl_socket* client_socket 
             = (tlsfront_ssl_socket*) app->new_tcp_connect (&app->m_local_addr
                                                            , &app->m_back_addr
                                                            , &app->m_stats_arr
                                                            , NULL
                                                            , &app->m_sock_opt);
            if (client_socket)
            {
                server_socket->m_session = new_sess;
                client_socket->m_session = new_sess;

                m_session->m_front_socket = server_socket;
                m_session->m_back_socket = client_socket;

                server_socket->m_other_socket = client_socket;
                client_socket->m_other_socket = server_socket;
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
        m_session->m_session_established = true;
    }
}

void tlsfront_ssl_socket::on_write ()
{
    if (this==m_session->m_front_socket && !m_ssl_init && !ssl_init())
    {
        this->abort();
        m_other_socket->abort();

        // todo???
    }
    else
    {    
        if (!m_write_buff_list.empty())
        {
            m_write_buff = m_write_buff_list.front();
            m_write_buff_list.pop();

            write_next_data (m_write_buff->m_buff
                                , 0
                                , m_write_buff->m_data_len
                                , false);
        }
    }
}

void tlsfront_ssl_socket::on_wstatus (int /*bytes_written*/, int write_status)
{
    ev_buff::free_ev_buff(m_write_buff);
    m_write_buff = nullptr;

    if (write_status == WRITE_STATUS_NORMAL)
    {
        //todo ???
    }
    else
    {
        //todo ??
    }
}

void tlsfront_ssl_socket::on_read ()
{
    if (this==m_session->m_front_socket && !m_ssl_init && !ssl_init())
    {
        this->abort();
        m_other_socket->abort();

        // todo???
    }
    else
    {
        ev_buff* rd_buff = ev_buff::alloc_ev_buff(2048);
        if (rd_buff)
        {
            m_read_buff = rd_buff;
            read_next_data (rd_buff->m_buff
                            , 0
                            , rd_buff->m_buff_len
                            , true);
        }
        else
        {
            //todo error handling
        }
    }
}

void tlsfront_ssl_socket::on_rstatus (int bytes_read, int read_status)
{
    if (bytes_read == 0)
    {
        if (m_session && m_session->m_session_established)
        {
            if (read_status == READ_STATUS_TCP_CLOSE) 
            {
                m_other_socket->write_close();
            }
            else
            {
                this->abort();
                m_other_socket->abort();
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

void tlsfront_ssl_socket::on_finish ()
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
