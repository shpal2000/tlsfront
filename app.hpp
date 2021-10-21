#ifndef __TLSFRONT_APP__H
#define __TLSFRONT_APP__H

#include "ev_app.hpp"

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <iostream>
#include <fstream>
#include<sstream>
#include <queue>
#include <cstring>
#include <string>
#include <thread>
#include <chrono>
#include <map>
#include <random>
#include <inttypes.h>

#include <subprojects/json/single_include/nlohmann/json.hpp>

using json = nlohmann::json;



enum enum_close_type { close_fin=1
                            , close_reset };

enum enum_close_notify { close_notify_no_send=1
                            , close_notify_send
                            ,  close_notify_send_recv};
                           
enum enum_tls_version { sslv3=0
                            , tls1
                            , tls1_1
                            , tls1_2
                            , tls1_3
                            , tls_all};

struct app_stats : public ev_sockstats
{
    static void dump_json_ev_sockstats (json& j, ev_sockstats* stats)
    {
        j["socketCreate"] = stats->socketCreate;
        j["socketCreateFail"] = stats->socketCreateFail;
        j["socketListenFail"] = stats->socketListenFail;
        j["socketReuseSet"] = stats->socketReuseSet;
        j["socketReuseSetFail"] = stats->socketReuseSetFail;
        j["socketIpTransparentSet"] = stats->socketIpTransparentSet;
        j["socketIpTransparentSetFail"] = stats->socketIpTransparentSetFail;
        j["socketLingerSet"] = stats->socketLingerSet;
        j["socketLingerSetFail"] = stats->socketLingerSetFail;
        j["socketBindIpv4"] = stats->socketBindIpv4;
        j["socketBindIpv4Fail"] = stats->socketBindIpv4Fail;
        j["socketBindIpv6"] = stats->socketBindIpv6;
        j["socketBindIpv6Fail"] = stats->socketBindIpv6Fail;

        j["socketConnectEstablishFail"] = stats->socketConnectEstablishFail;
        j["socketConnectEstablishFail2"] = stats->socketConnectEstablishFail2;

        j["tcpConnInit"] = stats->tcpConnInit;
        j["tcpConnInitInUse"] = stats->tcpConnInitInUse;
        j["tcpConnInitInSec"] = stats->tcpConnInitInSec;
        j["tcpConnInitRate"] = stats->tcpConnInitRate;
        j["tcpConnInitSuccess"] = stats->tcpConnInitSuccess;
        j["tcpConnInitSuccessInSec"] = stats->tcpConnInitSuccessInSec;
        j["tcpConnInitSuccessRate"] = stats->tcpConnInitSuccessRate;
        j["tcpConnInitFail"] = stats->tcpConnInitFail;
        j["tcpConnInitFailImmediateEaddrNotAvail"] = stats->tcpConnInitFailImmediateEaddrNotAvail;
        j["tcpConnInitFailImmediateOther"] = stats->tcpConnInitFailImmediateOther;
        j["tcpConnInitProgress"] = stats->tcpConnInitProgress;
        j["tcpWriteFail"] = stats->tcpWriteFail;
        j["tcpWriteReturnsZero"] = stats->tcpWriteReturnsZero;
        j["tcpReadFail"] = stats->tcpReadFail;

        j["tcpListenStart"] = stats->tcpListenStart;
        j["tcpListenStop"] = stats->tcpListenStop;
        j["tcpListenStartFail"] = stats->tcpListenStartFail;
        j["tcpAcceptFail"] = stats->tcpAcceptFail;
        j["tcpAcceptSuccess"] = stats->tcpAcceptSuccess;
        j["tcpAcceptSuccessInSec"] = stats->tcpAcceptSuccessInSec;
        j["tcpAcceptSuccessRate"] = stats->tcpAcceptSuccessRate;

        j["tcpLocalPortAssignFail"] = stats->tcpLocalPortAssignFail;
        j["tcpPollRegUnregFail"] = stats->tcpPollRegUnregFail;

        j["sslConnInit"] = stats->sslConnInit;
        j["sslConnInitInSec"] = stats->sslConnInitInSec;
        j["sslConnInitRate"] = stats->sslConnInitRate;
        j["sslConnInitSuccess"] = stats->sslConnInitSuccess;
        j["sslConnInitSuccessInSec"] = stats->sslConnInitSuccessInSec;
        j["sslConnInitSuccessRate"] = stats->sslConnInitSuccessRate;
        j["sslConnInitFail"] = stats->sslConnInitFail;
        j["sslConnInitProgress"] = stats->sslConnInitProgress;
        j["sslAcceptSuccess"] = stats->sslAcceptSuccess;
        j["sslAcceptSuccessInSec"] = stats->sslAcceptSuccessInSec;
        j["sslAcceptSuccessRate"] = stats->sslAcceptSuccessRate;

        j["tcpConnStructNotAvail"] = stats->tcpConnStructNotAvail;
        j["tcpListenStructNotAvail"] = stats->tcpListenStructNotAvail;
        j["appSessStructNotAvail"] = stats->appSessStructNotAvail;
        j["tcpInitServerFail"] = stats->tcpInitServerFail;
        j["tcpGetSockNameFail"] = stats->tcpGetSockNameFail;

        j["tcpActiveConns"] = stats->tcpActiveConns;
    }

    virtual void dump_json (json& j)
    {
        dump_json_ev_sockstats (j, this);
    };

};

class app : public ev_app
{
public:
    app()
    {
        
    }

    virtual ~app()
    {
    }

    virtual void run_iter(bool tick_sec)
    {
        ev_app::run_iter (tick_sec);
    }

    static void RunLoop(std::vector<app*> *app_list
                        , std::vector<app_stats*> *stats_list);
};

#endif