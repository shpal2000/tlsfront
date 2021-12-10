#ifndef __tlsclient_TCP_STATS__H
#define __tlsclient_TCP_STATS__H

#include "tlspack_app.hpp"

class tlsclient_socket;

struct tlsclient_stats_data : tlspack_app_stats
{
    uint64_t tlsclientThroughput;
    uint64_t tlsclientBytesInSec;

    virtual void tick_sec ()
    {
        tlspack_app_stats::tick_sec();

        tlsclientThroughput = tlsclientBytesInSec * 8;
        tlsclientBytesInSec = 0;
    }

    virtual void dump_json (json &j)
    {
        tlspack_app_stats::dump_json (j);
        
        j["tlsclientThroughput"] = tlsclientThroughput;
        j["tlsclientBytesInSec"] = tlsclientBytesInSec;
    }

    virtual ~tlsclient_stats_data() {};
};


struct tlsclient_stats : tlsclient_stats_data
{
    tlsclient_stats () : tlsclient_stats_data () {}
};

#endif