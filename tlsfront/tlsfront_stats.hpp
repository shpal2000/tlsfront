#ifndef __TLSFRONT_TCP_STATS__H
#define __TLSFRONT_TCP_STATS__H

#include "tlspack_app.hpp"

class tlsfront_socket;

struct tlsfront_stats_data : tlspack_app_stats
{
    uint64_t tlsfrontSessions;

    virtual void dump_json (json &j)
    {
        // tlspack_app_stats::dump_json (j);
        
        j["tlsfrontSessions"] = tlsfrontSessions;
    }

    virtual ~tlsfront_stats_data() {};
};


struct tlsfront_stats : tlsfront_stats_data
{
    tlsfront_stats () : tlsfront_stats_data () {}
};

#endif