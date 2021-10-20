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
};

/*
class tlsf_conn_grp
{
public:
    ev_socket_opt m_sock_opt;
    std::vector<ev_sockstats*> m_stats_arr;
    app_stats m_stats;

    app_stats* get_stats () {return &m_stats;}
    
    tlsf_conn_grp (json jcfg, app_stats* parent_stats) {
        m_sock_opt.rcv_buff_len = jcfg["tcp_rcv_buff"].get<uint32_t>();
        m_sock_opt.snd_buff_len = jcfg["tcp_snd_buff"].get<uint32_t>();

        m_stats_arr.push_back (&m_stats);
        m_stats_arr.push_back (parent_stats);
    }
};

class tlsf_cs_grp : public tlsf_conn_grp
{
public:

    std::vector<ev_sockaddrx*> m_clnt_addr_pool;
    int m_clnt_addr_index;
    int m_clnt_addr_count;

    ev_sockaddr m_srvr_addr;
    
    tlsf_cs_grp (json jcfg, app_stats* parent_stats)
                    : tlsf_conn_grp (jcfg, parent_stats)
    {

        auto srv_ip = jcfg["srv_ip"].get<std::string>();
        u_short srv_port = jcfg["srv_port"].get<u_short>();
        auto ip_begin = jcfg["clnt_ip_begin"].get<std::string>();
        auto ip_end = jcfg["clnt_ip_end"].get<std::string>();
        u_short port_begin = jcfg["clnt_port_begin"].get<u_short>();
        u_short port_end = jcfg["clnt_port_end"].get<u_short>();

        m_clnt_addr_index = 0;
        m_clnt_addr_count = 0;

        char next_ip[128];
        strcpy (next_ip, ip_begin.c_str());
        ev_sockaddrx* next_addr = new ev_sockaddrx (port_begin, port_end);
        ev_socket::set_sockaddr (&next_addr->m_addr, next_ip, 0);
        m_clnt_addr_pool.push_back(next_addr);
        m_clnt_addr_count++;

        while (strcmp(next_ip, ip_end.c_str()))
        {
            next_addr = new ev_sockaddrx (port_begin, port_end);
            ev_socket::get_nextip_str (next_ip, 1, next_ip);
            ev_socket::set_sockaddr (&next_addr->m_addr, next_ip, 0);
            m_clnt_addr_pool.push_back(next_addr);
            m_clnt_addr_count++;
        }

        ev_socket::set_sockaddr (&m_srvr_addr, srv_ip.c_str(), htons(srv_port));

    }

    ev_sockaddr* get_server_addr () {return &m_srvr_addr;};
    ev_sockaddrx* get_next_clnt_addr () 
    {
        ev_sockaddrx* ret = nullptr;
        if (m_clnt_addr_count > 0)
        {
            ret = m_clnt_addr_pool[m_clnt_addr_index];
            m_clnt_addr_index++;
            if (m_clnt_addr_index == m_clnt_addr_count)
            {
                m_clnt_addr_index = 0;
            }
            u_short port = ret->m_portq->get_port();
            if (port)
            {
                ev_socket::set_sockaddr_port(&ret->m_addr, port);
            }
            else
            {
                ret = nullptr;
            }
        }
        return ret;
    };
};

class app : public ev_app
{
public:
    app(json cfg_json, app_stats* group_stats);

    virtual ~app()
    {
    }

    virtual void run_iter(bool tick_sec)
    {
        ev_app::run_iter (tick_sec);
    }

    app_stats* get_stats(){
        return &m_stats;
    }


private:
    app_stats m_stats;

    ev_sockaddr m_server_addr;
    ev_sockaddr m_proxy_addr;
    std::vector<ev_sockaddrx*> m_client_addr_pool;

    int m_client_addr_index = 0;
    int m_client_addr_count = 0;

};

class tlsf_session;

class tlsf_socket : public ev_socket
{
public:
    tlsf_socket()
    {
        m_app = nullptr;
        m_session = nullptr;
    };

    virtual ~tlsf_socket()
    {

    };
    
    void on_establish ();
    void on_write ();
    void on_wstatus (int bytes_written, int write_status);
    void on_read ();
    void on_rstatus (int bytes_read, int read_status);
    void on_finish ();

public:
    tlsf_session* m_session;
    app* m_app;
};

class tlsf_session
{
public:

    tlsf_session()
    {
        m_server_sock = nullptr;
        m_client_sock = nullptr;
        m_session_established = false;

        m_client_current_wbuff = nullptr;
        m_server_current_wbuff = nullptr;

        m_client_current_rbuff = nullptr;
        m_server_current_rbuff = nullptr;
    }

    ~tlsf_session()
    {

    }
    
public:
    tlsf_socket* m_server_sock;
    tlsf_socket* m_client_sock;
    bool m_session_established;

    ev_buff* m_client_current_wbuff;
    ev_buff* m_server_current_wbuff;

    ev_buff* m_client_current_rbuff;
    ev_buff* m_server_current_rbuff;
    
    std::queue<ev_buff*> m_client_rbuffs;
    std::queue<ev_buff*> m_server_rbuffs;
};
*/

