
#include "tlsfront_app.hpp"

int main(int /*argc*/, char ** argv)
{
    signal(SIGPIPE, SIG_IGN);

    std::vector<tlspack_app*> app_list;
    std::vector<tlspack_app_stats*> stats_list;

    tlsfront_cfg ssl_app_cfg;
    tlsfront_stats ssl_app_gstats;

    ssl_app_cfg.front_ip = argv[1];
    ssl_app_cfg.front_port = std::stoi(argv[2]);

    ssl_app_cfg.server_ip = argv[3];
    ssl_app_cfg.server_port =  std::stoi(argv[4]);

    ssl_app_cfg.back_ip = argv[5];
    
    tlsfront_app* tcpApp 
        = new tlsfront_app(&ssl_app_cfg, &ssl_app_gstats);

    app_list.push_back(tcpApp);
    stats_list.push_back(&ssl_app_gstats);

    tlspack_app::RunLoop(&app_list, &stats_list);


    return 0;
}