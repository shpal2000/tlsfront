#ifndef __TLSFRONT_TCP_STATS__H
#define __TLSFRONT_TCP_STATS__H

#include "tlspack_app.hpp"

class tlsfront_socket;

struct tlsfront_stats_data : tlspack_app_stats
{
    uint64_t tlsfront_stats_1;
    uint64_t tlsfront_stats_100;

    virtual void dump_json (json &j)
    {
        tlspack_app_stats::dump_json (j);
        
        j["tlsfront_stats_1"] = tlsfront_stats_1;
        j["tlsfront_stats_100"] = tlsfront_stats_100;
    }

    virtual ~tlsfront_stats_data() {};
};


struct tlsfront_stats : tlsfront_stats_data
{
    tlsfront_stats () : tlsfront_stats_data () {}
};

#endif