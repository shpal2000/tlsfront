#ifndef __TLSFRONT_TCP_STATS__H
#define __TLSFRONT_TCP_STATS__H

#include "tlspack_app.hpp"

class tlsfront_tcp_socket;

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

#endif