#include "tlsfront_tcp_socket.hpp"
#include "tlsfront_tcp_session.hpp"

tlsfront_tcp_socket::tlsfront_tcp_socket()
{
    m_session = nullptr;
}

tlsfront_tcp_socket::~tlsfront_tcp_socket()
{

}

void tlsfront_tcp_socket::on_establish ()
{
    tlsfront_tcp_app* app = (tlsfront_tcp_app*) this->m_app;

    if (m_session == nullptr)
    {
        tlsfront_tcp_socket* server_socket = this;
        tlsfront_tcp_session* new_sess = new tlsfront_tcp_session();

        if (new_sess)
        {
            tlsfront_tcp_socket* client_socket 
             = (tlsfront_tcp_socket*) app->new_tcp_connect (&app->m_local_addr
                                                            , &app->m_back_addr
                                                            , &app->m_stats_arr
                                                            , NULL
                                                            , &app->m_sock_opt);
            if (client_socket)
            {
                client_socket->m_session = new_sess;
                server_socket->m_session = new_sess;
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