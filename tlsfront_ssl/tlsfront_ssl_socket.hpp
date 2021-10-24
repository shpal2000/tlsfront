#ifndef __TLSFRONT_TCP_SOCKET__H
#define __TLSFRONT_TCP_SOCKET__H

#include "tlsfront_ssl_app.hpp"

class tlsfront_ssl_session;

class tlsfront_ssl_socket : public ev_socket
{
public:
    tlsfront_ssl_socket(SSL_CTX* s_ssl_ctx, SSL_CTX* c_ssl_ctx);
    virtual ~tlsfront_ssl_socket();
    
    void on_establish ();
    void on_write ();
    void on_wstatus (int bytes_written, int write_status);
    void on_read ();
    void on_rstatus (int bytes_read, int read_status);
    void on_finish ();

public:
    tlsfront_ssl_session* m_session;

    tlsfront_ssl_socket* m_other_socket;

    ev_buff* m_read_buff;
    ev_buff* m_write_buff;

    std::queue<ev_buff*> m_write_buff_list;

private:
    bool ssl_server_init();
    bool ssl_client_init();

private:
    bool m_ssl_init;
    SSL_CTX* m_s_ssl_ctx;
    SSL_CTX* m_c_ssl_ctx;
    SSL* m_ssl;
};

#endif