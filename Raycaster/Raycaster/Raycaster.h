#pragma once

#include "IGameLoop.h"

#include "Camera.h"
#include "Ray.h"
#include "Renderer.h"
#include "World.h"

class Raycaster : public IGameLoop
{
public:
    Raycaster();

    virtual void Init() override;
    virtual void Render() override;
    virtual void Update(uint32_t delta_ticks) override;

    virtual void OnKeyDown(SDL_Keycode key) override;
    virtual void OnKeyUp(SDL_Keycode key) override;

private:
    void DrawStripe(uint32_t y, uint32_t length);
    float RoundUpToMultipleOf(float to_round, int32_t multiple);
    int32_t RoundDownToMultipleOf(float to_round, int32_t multiple);
	Ray CastRay(const Ray& ray);

private:
    Camera camera_;
    World world_;
    Renderer renderer_;

private:
    static const float kInitialPosX;
    static const float kInitialPosY;
    static const float kInitialPosOrientationDeg;
    static const int32_t kfieldOfView = 60;
    static const int32_t kHeight = 32;
    static const int32_t kUnitsPerBlock = 64;
    static const float kMovementUnitsPerSec;
    static const int32_t kFramebufferWidth = 480;
    static const int32_t kFramebufferHeight = 640;
};

