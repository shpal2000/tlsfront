
#include "app.hpp"

tlsf_app::tlsf_app(json jcfg
                , tlsf_stats* group_stats)
{
    //m_group_stats = group_stats;

    auto proxy_ip = jcfg["proxy_ip"].get<std::string>();
    auto proxy_port = jcfg["proxy_port"].get<int>();

    auto server_ip = jcfg["server_ip"].get<std::string>();
    auto server_port = jcfg["server_port"].get<int>();

    u_short port_begin = jcfg["clnt_port_begin"].get<u_short>();
    u_short port_end = jcfg["clnt_port_end"].get<u_short>();

    auto client_ip_list = jcfg["client_ips"];

    for (auto it = client_ip_list.begin(); it != client_ip_list.end(); ++it)
    {
        auto client_ip = it.value().get<std::string>();

        char next_ip[128];
        strcpy (next_ip, client_ip.c_str());

        ev_sockaddrx* next_addr = new ev_sockaddrx (port_begin, port_end);
        ev_socket::set_sockaddr (&next_addr->m_addr, next_ip, 0);
        m_clnt_addr_pool.push_back(next_addr);
        m_clnt_addr_count++;
    }
}

int main(int /*argc*/, char ** /*argv*/)
{
    return 0;
}