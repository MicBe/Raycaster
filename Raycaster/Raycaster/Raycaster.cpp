#include "Raycaster.h"

#include <SDL.h>

#include <iostream>

Raycaster::Raycaster()
    :camera_(kInitialPosX, kInitialPosY,
             kInitialPosOrientationDeg,
             kfieldOfView, kHeight,
             kMovementUnitsPerSec),
    world_(kUnitsPerBlock),
    renderer_(kFramebufferWidth, kFramebufferHeight)
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

    const float increment = (camera_.fov() / 2) / kFramebufferWidth;
    float ray_angle = camera_.orientation_deg() - (camera_.fov() / 2);

    for (int32_t ray_index = 0; ray_index < kFramebufferWidth; ++ray_index)
    {
        // Orientation upward?
        if (camera_.orientation_deg() > 0 && camera_.orientation_deg() <= 180.0f)
        {
            float nextX = RoundUpToMultipleOf(camera_.position_x(), world_.units_per_block());
            float nextY = RoundUpToMultipleOf(camera_.position_y(), world_.units_per_block());
        }

        // Draw line that corresponds to the distance

        ray_angle += increment;
    }
}

void Raycaster::OnKeyDown(SDL_Keycode key)
{
    std::cout << "Key down: " << key << std::endl;
}

void Raycaster::OnKeyUp(SDL_Keycode key)
{
    std::cout << "Key up: " << key << std::endl;
}

float Raycaster::RoundUpToMultipleOf(float to_round, int32_t multiple)
{
    if (multiple == 0)
        return to_round;
    int32_t next_int = ceil(to_round);
    int32_t remainder = next_int % multiple;
    if (remainder == 0)
        return to_round;
    return static_cast<float>(to_round + multiple - remainder);
}

const float Raycaster::kInitialPosX = 96.0f;
const float Raycaster::kInitialPosY = 96.0f;
const float Raycaster::kInitialPosOrientationDeg = 90.0f;
const float Raycaster::kMovementUnitsPerSec = 64.0f;
