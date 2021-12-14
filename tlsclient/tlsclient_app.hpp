#ifndef __tlsclient_TCP_APP__H
#define __tlsclient_TCP_APP__H

#include "tlspack_app.hpp"

#include "tlsclient_cfg.hpp"
#include "tlsclient_stats.hpp"

class tlsclient_socket;

struct tlsclient_grp_ctx
{
    SSL_CTX* m_c_ssl_ctx;
};

struct tlsclient_app_ctx
{
    ev_sockaddr m_server_addr;
    ev_sockaddr m_stats_addr;
    
    ev_socket_opt m_sock_opt;
    
    std::vector<ev_sockstats*> m_stats_arr;
    
    tlsclient_socket* m_stats_sock;

    std::string m_app_id; 

    int m_server_ssl;

    int m_send_recv_len;

    int m_send_buff_len;
    char* m_send_buff;

    int m_recv_buff_len;
    char* m_recv_buff;

    int m_cps;
    uint64_t m_total_conn_count;
    uint64_t m_max_active_conn_count;
};

class tlsclient_app : public tlspack_app
{
public:
    tlsclient_app(tlsclient_cfg* cfg, tlsclient_stats* gstats);

    virtual ~tlsclient_app();

    void run_iter(bool tick_sec);
    
    ev_socket* alloc_socket(bool is_udp=false);
    
    void free_socket(ev_socket* ev_sock);

    tlsclient_stats m_stats;

    tlsclient_app_ctx m_app_ctx;
    tlsclient_grp_ctx m_grp_ctx;

    bool m_init_ok;

    bool to_new_connect ();

    bool m_stop;
    uint64_t m_curr_conn_count;
    std::chrono::steady_clock::time_point m_conn_init_time;
};


#define inc_tlsclient_stats(__stat_name) \
{ \
    for (uint i=0; i < this->get_sockstats_arr()->size(); i++) { \
        ev_sockstats* __stats_ptr = (*(this->get_sockstats_arr()))[i]; \
        ((tlsclient_stats*)(__stats_ptr))->__stat_name++; \
    } \
}

#define dec_tlsclient_stats(__stat_name) \
{ \
    for (uint i=0; i < this->get_sockstats_arr()->size(); i++) { \
        ev_sockstats* __stats_ptr = (*(this->get_sockstats_arr()))[i]; \
        ((tlsclient_stats*)(__stats_ptr))->__stat_name--; \
    } \
}

#define add_tlsclient_stats(__stat_name,__value) \
{ \
    for (uint i=0; i < this->get_sockstats_arr()->size(); i++) { \
        ev_sockstats* __stats_ptr = (*(this->get_sockstats_arr()))[i]; \
        ((tlsclient_stats*)(__stats_ptr))->__stat_name += (__value); \
    } \
}

#define sub_tlsclient_stats(__stat_name,__value) \
{ \
    for (uint i=0; i < this->get_sockstats_arr()->size(); i++) { \
        ev_sockstats* __stats_ptr = (*(this->get_sockstats_arr()))[i]; \
        ((tlsclient_stats*)(__stats_ptr))->__stat_name -= (__value); \
    } \
}

#endif