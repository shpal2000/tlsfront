
#include "app.hpp"

void app::RunLoop(std::vector<app*> *app_list
                    , std::vector<app_stats*> *stats_list)
{
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

        for (app* app_ptr : *app_list)
        {
            app_ptr->run_iter (is_tick_sec);
        }

        if (is_tick_sec) 
        {
            for (app_stats* stats_ptr : *stats_list)
            {
                stats_ptr->tick_sec();
            }

            is_tick_sec = false;
        }
    }
}