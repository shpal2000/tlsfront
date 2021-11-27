
#include "tlspack_app.hpp"

tlspack_app::tlspack_app()
{

}

tlspack_app::~tlspack_app()
{

}

void tlspack_app::run_iter(bool tick_sec)
{
    ev_app::run_iter (tick_sec);
}

void tlspack_app::RunLoop(std::vector<tlspack_app*> *app_list
                    , std::vector<tlspack_app_stats*> *stats_list)
{
    std::chrono::time_point<std::chrono::system_clock> start, current;
    start = std::chrono::system_clock::now();
    bool is_tick_sec = false;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1));

        current = std::chrono::system_clock::now();

        auto ms_elapsed 
         = std::chrono::duration_cast<std::chrono::milliseconds> (current-start);

        if (ms_elapsed.count() >= 1000)
        {
            start = current;
            is_tick_sec = true;
        }

        for (tlspack_app* app_ptr : *app_list)
        {
            app_ptr->run_iter (is_tick_sec);
        }

        if (is_tick_sec) 
        {
            for (tlspack_app_stats* stats_ptr : *stats_list)
            {
                stats_ptr->tick_sec();
            }

            is_tick_sec = false;
        }
    }
}