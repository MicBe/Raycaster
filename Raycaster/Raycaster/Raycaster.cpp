#include "Raycaster.h"

#include <SDL.h>

#include <iostream>

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

void Raycaster::Update(uint32_t delta_ticks)
{
    const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
    if (keyboardState[SDL_SCANCODE_UP])
        camera_.GoForward(delta_ticks);
    if (keyboardState[SDL_SCANCODE_DOWN])
        camera_.GoBackward(delta_ticks);
    if (keyboardState[SDL_SCANCODE_LEFT])
        camera_.RotateLeft(delta_ticks);
    if (keyboardState[SDL_SCANCODE_RIGHT])
        camera_.RotateRight(delta_ticks);

    system("cls");
    std::cout << "Camera x: " << camera_.position_x() << std::endl;
    std::cout << "Camera y: " << camera_.position_y() << std::endl;
    std::cout << "Orientation: " << camera_.orientation_deg() << std::endl;
}

void Raycaster::OnKeyDown(SDL_Keycode key)
{
    std::cout << "Key down: " << key << std::endl;
}

void Raycaster::OnKeyUp(SDL_Keycode key)
{
    std::cout << "Key up: " << key << std::endl;
}

const float Raycaster::kInitialPosY = 96.0f;
const float Raycaster::kInitialPosX = 96.0f;
const float Raycaster::kInitialPosOrientationDeg = 90.0f;
const float Raycaster::kMovementUnitsPerSec = 64.0f;
