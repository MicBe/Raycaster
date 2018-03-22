#pragma once

#include <SDL.h>

#include <memory>

class IGameLoop;

class GameLoop
{
public:
    GameLoop(std::unique_ptr<IGameLoop> gameloop);
    void Run();

private:
    std::unique_ptr<IGameLoop> concrete_gameloop_;
    SDL_Window* window_;
};


