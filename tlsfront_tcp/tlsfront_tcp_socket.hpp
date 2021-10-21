#ifndef __TLSFRONT_TCP_SOCKET__H
#define __TLSFRONT_TCP_SOCKET__H

class tlsfront_tcp_session;
class tlsfront_tcp_app;

class tlsfront_tcp_socket : public ev_socket
{
public:
    tlsfront_tcp_socket();
    virtual ~tlsfront_tcp_socket();
    
    void on_establish ();
    void on_write ();
    void on_wstatus (int bytes_written, int write_status);
    void on_read ();
    void on_rstatus (int bytes_read, int read_status);
    void on_finish ();

public:
    tlsfront_tcp_session* m_session;
    tlsfront_tcp_app* m_app;
};

#endif