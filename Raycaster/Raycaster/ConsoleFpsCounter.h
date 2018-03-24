#pragma once

#include <array>
#include <cstdint>

class ConsoleFpsCounter
{
public:
    ConsoleFpsCounter();
    void FrameFinished(uint32_t delta_ticks);
    
private:
    uint32_t frame_count_;
    uint32_t ticks_cumul_;
};
