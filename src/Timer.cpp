#include "Timer.hpp"

Timer::Timer()
{
    start_ticks_ = 0;
    paused_ticks_ = 0;

    is_started_ = false;
    is_paused_ = false;
}

Timer::~Timer()
{

}

void Timer::Start()
{
    is_started_ = true;
    is_paused_ = false;

    start_ticks_ = SDL_GetTicks();
    paused_ticks_ = 0;
}

void Timer::Stop()
{
    is_started_ = false;
    is_paused_ = false;

    start_ticks_ = 0;
    paused_ticks_ = 0;
}

void Timer::Pause()
{
    if (is_started_ && !is_paused_)
    {
        is_paused_ = true;

        cout << "Paused!" << endl;
        paused_ticks_ = SDL_GetTicks() - start_ticks_;
        start_ticks_ = 0;
    }
}

void Timer::Unpause()
{
    if (is_started_ && is_paused_)
    {
        is_paused_ = false;
        
        start_ticks_ = SDL_GetTicks() - paused_ticks_;
        paused_ticks_ = 0;
    }
}

Uint32 Timer::GetTicks()
{
    Uint32 time = 0;
    if (is_started_)
    {
        if (is_paused_)
        {
            time = paused_ticks_;
        }
        else
        {
            time = SDL_GetTicks() - start_ticks_;
        }
    }

    return time;
}

bool Timer::IsStarted()
{
    return is_started_;
}

bool Timer::IsPaused()
{
    return is_started_ && is_paused_;
}