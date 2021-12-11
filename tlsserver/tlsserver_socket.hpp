#ifndef __tlsserver_TCP_SOCKET__H
#define __tlsserver_TCP_SOCKET__H

#include "tlsserver_app.hpp"

class tlsserver_session;

class tlsserver_socket : public ev_socket
{
public:
    tlsserver_socket(bool is_udp=false);
    virtual ~tlsserver_socket();
    
    void on_establish ();
    void on_write ();
    void on_wstatus (int bytes_written, int write_status);
    void on_read ();
    void on_rstatus (int bytes_read, int read_status);
    void on_error ();
    void on_finish ();


public:
    
    tlsserver_app_ctx* m_app_ctx;
    tlsserver_grp_ctx* m_grp_ctx;

private:
    bool ssl_server_init();
    void set_context_from(tlsserver_socket* from_sock);
    void set_context_from_parent();
    void abort_session();

private:
    bool m_ssl_init;
    bool m_write_close_marked;
    SSL* m_ssl;

    int m_bytes_read;
    int m_bytes_written;
};
#endif