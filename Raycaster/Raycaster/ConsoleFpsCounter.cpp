#include "ConsoleFpsCounter.h"

#include <SDL.h>

#include <iostream>
#include <numeric>

ConsoleFpsCounter::ConsoleFpsCounter()
    :frame_count_(0),
    last_ticks_(0),
    ticks_cumul_(0)
{
}

void ConsoleFpsCounter::FrameFinished()
{
    ++frame_count_;

    const uint32_t current_ticks = SDL_GetTicks();
    const uint32_t delta_ticks = current_ticks - last_ticks_;
    last_ticks_ = current_ticks;
    ticks_cumul_ += delta_ticks;
    if (ticks_cumul_ >= 1000)
    {
        std::cout << "Fps: " << frame_count_ << '\n';
        frame_count_ = 0;
        ticks_cumul_ = 0;
    }
}
