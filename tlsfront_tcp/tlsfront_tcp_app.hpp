#ifndef __TLSFRONT_TCP_APP__H
#define __TLSFRONT_TCP_APP__H

#include "app.hpp"

struct tlsfront_tcp_stats_data : app_stats
{
    uint64_t tlsfront_tcp_stats_1;
    uint64_t tlsfront_tcp_stats_100;

    virtual void dump_json (json &j)
    {
        app_stats::dump_json (j);
        
        j["tlsfront_tcp_stats_1"] = tlsfront_tcp_stats_1;
        j["tlsfront_tcp_stats_100"] = tlsfront_tcp_stats_100;
    }

    virtual ~tlsfront_tcp_stats_data() {};
};


struct tlsfront_tcp_stats : tlsfront_tcp_stats_data
{
    tlsfront_tcp_stats () : tlsfront_tcp_stats_data () {}
};


struct tlsfront_tcp_cfg
{
    std::string front_ip;
    u_short front_port;

    std::string back_ip;
    u_short back_port;

};


class tlsfront_tcp_app : public app
{
public:
    tlsfront_tcp_app(tlsfront_tcp_cfg* cfg, tlsfront_tcp_stats* gstats);

    virtual ~tlsfront_tcp_app();

private:
    ev_sockaddr m_front_addr;
    ev_sockaddr m_back_addr;
    ev_socket_opt m_sock_opt;
    tlsfront_tcp_stats m_stats;
    std::vector<ev_sockstats*> m_stats_arr;

    tlsfront_tcp_socket* m_front_lsocket;
};
#endif