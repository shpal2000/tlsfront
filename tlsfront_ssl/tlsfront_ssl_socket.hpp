#ifndef __TLSFRONT_TCP_SOCKET__H
#define __TLSFRONT_TCP_SOCKET__H

#include "tlsfront_ssl_app.hpp"

class tlsfront_ssl_session;

class tlsfront_ssl_socket : public ev_socket
{
public:
    tlsfront_ssl_socket();
    virtual ~tlsfront_ssl_socket();
    
    void on_establish ();
    void on_write ();
    void on_wstatus (int bytes_written, int write_status);
    void on_read ();
    void on_rstatus (int bytes_read, int read_status);
    void on_finish (bool is_error);

public:
    tlsfront_ssl_session* m_session;

    tlsfront_ssl_socket* m_other_socket;

    ev_buff* m_read_buff;
    std::queue<ev_buff*> m_write_buff_list;
    
    tlsfront_ssl_app_ctx* m_app_ctx;
    tlsfront_ssl_grp_ctx* m_grp_ctx;

private:
    bool ssl_server_init();
    bool ssl_client_init();
    void set_context_from(tlsfront_ssl_socket* from_sock);
    void set_context_from_parent();

private:
    bool m_ssl_init;
    SSL* m_ssl;
};

#endif