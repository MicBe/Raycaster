#pragma once

#include <SDL.h>

class IGameLoop
{
public:
    IGameLoop() = default;
    IGameLoop(const IGameLoop&) = default;
    IGameLoop(IGameLoop&&) = default;
    IGameLoop& operator=(const IGameLoop&) = default;
    IGameLoop& operator=(IGameLoop&&) = default;
    virtual ~IGameLoop() = default;

    virtual void Init() = 0;
    virtual void Render() = 0;
    virtual void Update(uint32_t delta_ticks) = 0;

    virtual void OnKeyDown(SDL_Keycode key);
    virtual void OnKeyUp(SDL_Keycode key);
};

