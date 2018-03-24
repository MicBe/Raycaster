#include "TicksCounter.h"

#include <SDL.h>


TicksCounter::TicksCounter()
    :last_ticks_(SDL_GetTicks()),
    delta_ticks_(0)
{
}

uint32_t TicksCounter::Update()
{
    uint32_t current_ticks = SDL_GetTicks();
    delta_ticks_ = current_ticks - last_ticks_;
    last_ticks_ = current_ticks;
    return delta_ticks_;
}
