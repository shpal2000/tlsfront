
#include "tlsfront_tcp_app.hpp"


int main(int /*argc*/, char ** /*argv*/)
{
    tlsfront_tcp_cfg tcp_app_cfg;
    tlsfront_tcp_stats tcp_app_gstats;


    tcp_app_cfg.front_ip = "172.16.5.4";
    tcp_app_cfg.front_port = 5555;
    tcp_app_cfg.back_ip = "52.40.35.216";
    tcp_app_cfg.back_port = 80;

    
    tlsfront_tcp_app* tcpApp = new tlsfront_tcp_app(&tcp_app_cfg, &tcp_app_gstats);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    bool is_tick_sec = false;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1));

        auto ms_elapsed 
                = std::chrono::duration_cast<std::chrono::milliseconds> (end-start);

        if (ms_elapsed.count() >= 1000)
        {
            start = end;
            is_tick_sec = true;
        }

        tcpApp->run_iter(is_tick_sec);


        if (is_tick_sec) 
        {
            tcp_app_gstats.tick_sec();

            is_tick_sec = false;
        }
    }
    

    return 0;
}