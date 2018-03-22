#include "Raycaster.h"


Raycaster::Raycaster()
    :camera_(kInitialPosX, kInitialPosY,
             kInitialPosOrientationDeg,
             kfieldOfView, kHeight,
             kMovementUnitsPerSec),
    world_(kUnitsPerBlock),
    graphics_()
{
}

void Raycaster::Init()
{
    graphics_.Init();
}

void Raycaster::Render()
{
    graphics_.Render();
}

void Raycaster::Update()
{
    graphics_.Update();
}

const float Raycaster::kInitialPosY = 96.0f;
const float Raycaster::kInitialPosX = 96.0f;
const float Raycaster::kMovementUnitsPerSec = 64.0f;
