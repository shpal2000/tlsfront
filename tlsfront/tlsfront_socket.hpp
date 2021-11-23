#ifndef __TLSFRONT_TCP_SOCKET__H
#define __TLSFRONT_TCP_SOCKET__H

#include "tlsfront_app.hpp"

class tlsfront_session;

class tlsfront_socket : public ev_socket
{
public:
    tlsfront_socket();
    virtual ~tlsfront_socket();
    
    void on_establish ();
    void on_write ();
    void on_wstatus (int bytes_written, int write_status);
    void on_read ();
    void on_rstatus (int bytes_read, int read_status);
    void on_error ();
    void on_finish ();


public:
    tlsfront_session* m_session;

    tlsfront_socket* m_other_socket;

    ev_buff* m_read_buff;
    std::queue<ev_buff*> m_write_buff_list;
    
    tlsfront_app_ctx* m_app_ctx;
    tlsfront_grp_ctx* m_grp_ctx;

private:
    bool ssl_server_init();
    bool ssl_client_init();
    void set_context_from(tlsfront_socket* from_sock);
    void set_context_from_parent();
    void abort_session();

private:
    bool m_ssl_init;
    bool m_write_close_marked;
    SSL* m_ssl;
};

#endif