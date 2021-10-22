
#include "tlsfront_tcp_app.hpp"


int main(int /*argc*/, char ** /*argv*/)
{
    std::vector<app*> app_list;
    std::vector<app_stats*> stats_list;

    tlsfront_tcp_cfg tcp_app_cfg;
    tlsfront_tcp_stats tcp_app_gstats;

    tcp_app_cfg.front_ip = "172.16.5.4";
    tcp_app_cfg.front_port = 5555;
    tcp_app_cfg.back_ip = "52.40.35.216";
    tcp_app_cfg.back_port = 80;

    
    tlsfront_tcp_app* tcpApp = new tlsfront_tcp_app(&tcp_app_cfg, &tcp_app_gstats);

    app_list.push_back(tcpApp);
    stats_list.push_back(&tcp_app_gstats);


    app::RunLoop(&app_list, &stats_list);
    

    return 0;
}