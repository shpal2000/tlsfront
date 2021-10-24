
#include "tlsfront_ssl_app.hpp"

#include <signal.h>

int main(int /*argc*/, char ** /*argv*/)
{
    std::vector<tlspack_app*> app_list;
    std::vector<tlspack_app_stats*> stats_list;

    tlsfront_ssl_cfg ssl_app_cfg;
    tlsfront_ssl_stats ssl_app_gstats;

    ssl_app_cfg.front_ip = "172.16.5.4";
    ssl_app_cfg.front_port = 5556;
    ssl_app_cfg.back_ip = "54.148.237.114";
    ssl_app_cfg.back_port = 443;

    
    tlsfront_ssl_app* tcpApp 
        = new tlsfront_ssl_app(&ssl_app_cfg, &ssl_app_gstats);

    app_list.push_back(tcpApp);
    stats_list.push_back(&ssl_app_gstats);


    tlspack_app::RunLoop(&app_list, &stats_list);
    

    return 0;
}