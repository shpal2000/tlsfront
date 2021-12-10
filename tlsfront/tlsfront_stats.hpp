#ifndef __TLSFRONT_TCP_STATS__H
#define __TLSFRONT_TCP_STATS__H

#include "tlspack_app.hpp"

class tlsfront_socket;

struct tlsfront_stats_data : tlspack_app_stats
{
    uint64_t tlsfrontSessions;
    uint64_t tlsfrontActSessions;
    uint64_t tlsfrontThroughput;
    uint64_t tlsfrontBytesInSec;

    virtual void tick_sec ()
    {
        tlspack_app_stats::tick_sec();

        tlsfrontThroughput = tlsfrontBytesInSec * 8;
        // tlsfrontBytesInSec = 0;
    }

    virtual void dump_json (json &j)
    {
        tlspack_app_stats::dump_json (j);
        
        j["tlsfrontSessions"] = tlsfrontSessions;
        j["tlsfrontActSessions"] = tlsfrontActSessions;
        j["tlsfrontThroughput"] = tlsfrontThroughput;
    }

    virtual ~tlsfront_stats_data() {};
};


struct tlsfront_stats : tlsfront_stats_data
{
    tlsfront_stats () : tlsfront_stats_data () {}
};

#endif