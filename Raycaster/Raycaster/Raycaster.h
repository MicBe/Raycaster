#pragma once

#include "IRenderable.h"

#include "Camera.h"
#include "Renderer.h"
#include "World.h"

class Raycaster : public IRenderable
{
public:
    Raycaster();

    virtual void Init() override;
    virtual void Render() override;
    virtual void Update() override;

private:
    Camera camera_;
    World world_;
    Renderer renderer_;

private:
    static const float kInitialPosX;
    static const float kInitialPosY;
    static const int32_t kInitialPosOrientationDeg = 135;
    static const int32_t kfieldOfView = 60;
    static const int32_t kHeight = 32;
    static const int32_t kUnitsPerBlock = 64;
    static const float kMovementUnitsPerSec;
};

