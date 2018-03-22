#pragma once

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
    virtual void Update() = 0;
};

