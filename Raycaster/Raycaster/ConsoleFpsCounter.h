#pragma once

#include <array>
#include <cstdint>

class ConsoleFpsCounter
{
public:
    ConsoleFpsCounter();
    void FrameFinished();
    
private:
    uint32_t frame_count_;
    uint32_t last_ticks_;
    uint32_t ticks_cumul_;
};
