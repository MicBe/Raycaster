#pragma once

#include <SDL.h>

class RenderingLoop
{
public:
    RenderingLoop();
    void Run();

private:
    SDL_Window* m_window;
};


