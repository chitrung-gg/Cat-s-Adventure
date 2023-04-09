#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "CommonFunction.hpp"

class Timer
{
    public:
        Timer();
        ~Timer();

        void Start();
        void Stop();
        void Pause();
        void Unpause();

        Uint32 GetTicks();

        bool IsStarted();
        bool IsPaused();

    private:
        Uint32 start_ticks_;
        Uint32 paused_ticks_;

        bool is_started_;
        bool is_paused_;
};
#endif