
#include "tlsfront_app.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main(int /*argc*/, char ** /*argv*/)
{
    signal(SIGPIPE, SIG_IGN);

    const char* cfg_file = "/configs/config.json";

    std::ifstream cfg_stream(cfg_file);
    json cfg_json = json::parse(cfg_stream);

    std::vector<tlspack_app*> app_list;
    std::vector<tlspack_app_stats*> stats_list;

    tlsfront_cfg app_cfg;
    tlsfront_stats app_gstats;

    app_cfg.m_app_id = cfg_json["app_id"].get<std::string>();

    app_cfg.front_ip = cfg_json["front_ip"].get<std::string>();
    app_cfg.front_port = cfg_json["front_port"].get<int>();

    app_cfg.server_ip = cfg_json["server_ip"].get<std::string>();
    app_cfg.server_port = cfg_json["server_port"].get<int>();

    app_cfg.back_ip = cfg_json["back_ip"].get<std::string>();

    app_cfg.stats_ip = cfg_json["stats_ip"].get<std::string>();
    app_cfg.stats_port = cfg_json["stats_port"].get<int>();

    app_cfg.monitor_ip = cfg_json["monitor_ip"].get<std::string>();
    app_cfg.monitor_port = cfg_json["monitor_port"].get<int>();

    tlsfront_app* tcpApp 
        = new tlsfront_app(&app_cfg, &app_gstats);

    app_list.push_back(tcpApp);
    stats_list.push_back(&app_gstats);

    tlspack_app::RunLoop(&app_list, &stats_list);


    return 0;
}