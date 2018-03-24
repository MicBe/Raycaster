#pragma once

#include <cstdint>

class TicksCounter
{
public:
    TicksCounter();
    uint32_t Update();

private:
    uint32_t last_ticks_;
    uint32_t delta_ticks_;
};

