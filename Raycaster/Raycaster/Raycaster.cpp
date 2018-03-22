#include "Raycaster.h"


Raycaster::Raycaster()
    :camera_(kInitialPosX, kInitialPosY,
             kInitialPosOrientationDeg,
             kfieldOfView, kHeight,
             kMovementUnitsPerSec),
    world_(kUnitsPerBlock),
    renderer_()
{
}

void Raycaster::Init()
{
    renderer_.Init();
}

void Raycaster::Render()
{
    renderer_.Render();
}

void Raycaster::Update()
{
    renderer_.Update();
}

const float Raycaster::kInitialPosY = 96.0f;
const float Raycaster::kInitialPosX = 96.0f;
const float Raycaster::kMovementUnitsPerSec = 64.0f;
