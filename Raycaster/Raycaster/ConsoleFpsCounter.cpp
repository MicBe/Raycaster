#include "ConsoleFpsCounter.h"

#include <SDL.h>

#include <iostream>
#include <numeric>

ConsoleFpsCounter::ConsoleFpsCounter()
    :frame_count_(0),
    ticks_cumul_(0)
{
}

void ConsoleFpsCounter::FrameFinished(uint32_t delta_ticks)
{
    ++frame_count_;

    ticks_cumul_ += delta_ticks;
    if (ticks_cumul_ >= 1000)
    {
        std::cout << "Fps: " << frame_count_ << '\r';
        frame_count_ = 0;
        ticks_cumul_ = 0;
    }
}
