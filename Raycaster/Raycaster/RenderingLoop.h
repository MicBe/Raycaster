#pragma once

#include <SDL.h>

#include <memory>

class IRenderable;

class RenderingLoop
{
public:
    RenderingLoop(std::unique_ptr<IRenderable> renderable);
    void Run();

private:
    std::unique_ptr<IRenderable> renderable_;
    SDL_Window* window_;
};


