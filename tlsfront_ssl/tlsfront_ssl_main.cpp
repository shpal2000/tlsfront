
#include "tlsfront_ssl_app.hpp"

#include <signal.h>

int main(int /*argc*/, char ** /*argv*/)
{
    signal(SIGPIPE, SIG_IGN);

    std::vector<tlspack_app*> app_list;
    std::vector<tlspack_app_stats*> stats_list;

    tlsfront_ssl_cfg ssl_app_cfg;
    tlsfront_ssl_stats ssl_app_gstats;

    ssl_app_cfg.front_ip = "127.0.0.1";
    ssl_app_cfg.front_port = 5556;

    ssl_app_cfg.server_ip = "172.217.14.228";
    ssl_app_cfg.server_port = 443;

    ssl_app_cfg.back_ip = "172.16.5.4";

    
    tlsfront_ssl_app* tcpApp 
        = new tlsfront_ssl_app(&ssl_app_cfg, &ssl_app_gstats);

    app_list.push_back(tcpApp);
    stats_list.push_back(&ssl_app_gstats);

    
    std::cout << "https://127.0.0.1:5556" << "\n\n";

    fflush(stdout);


    tlspack_app::RunLoop(&app_list, &stats_list);


    return 0;
}