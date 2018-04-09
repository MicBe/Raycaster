#include "Raycaster.h"

#include <glm/glm.hpp>
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

    const float increment = static_cast<float>(camera_.fov()) / static_cast<float>(kFramebufferHeight);
    float ray_angle = camera_.orientation_deg() - (camera_.fov() / 2);

    for (int32_t ray_index = 0; ray_index < kFramebufferHeight; ++ray_index)
    {
        DrawCenteredHorizontalLine(ray_index, kFramebufferWidth * ((float)ray_index / (float)kFramebufferHeight));
        
        Ray ray(glm::vec2(camera_.position_x(), camera_.position_y()), ray_angle);
        const Ray casted_ray = CastRay(ray);
		if (casted_ray.collided_)
		{
            const float distanceX = casted_ray.dest_.x - camera_.position_x();
            const float distanceY = casted_ray.dest_.y - camera_.position_y();

            const float distance = glm::sqrt(glm::pow(distanceX, 2) + glm::pow(distanceY, 2));

			// Draw wall
		}

        ray_angle += increment;
    }
}

Ray Raycaster::CastRay(const Ray& ray)
{
    Ray result(ray);
	float pos_x = ray.origin_.x;
	float pos_y = ray.origin_.y;
    do 
    {
        const float next_x = RoundUpToMultipleOf(pos_x, world_.units_per_block());
        const float next_y = RoundUpToMultipleOf(pos_y, world_.units_per_block());

        // Find nearest distance between going to next x or next y
        const float dist_x = (next_x - pos_x) / cos(glm::radians(ray.angle_));
        const float dist_y = (next_y - pos_y) / sin(glm::radians(ray.angle_));

        if (dist_x <= dist_y)
        {
            // Next x has nearest distance?
            pos_y = pos_y + (dist_x * glm::sin(glm::radians(ray.angle_)));
            pos_x = next_x;
        }
        else
        {
            // Next y has nearest distance?
            pos_x = pos_x + (dist_y * glm::cos(glm::radians(ray.angle_)));
            pos_y = next_y;
        }

        if (world_.IsInsideBlock(pos_x, pos_y))
        {
            result.collided_ = true;
            result.dest_.x = pos_x;
            result.dest_.y = pos_y;
            return result;
        }

    } while (world_.IsInside(pos_x, pos_y) && !result.collided_);

    return result;
}

void Raycaster::OnKeyDown(SDL_Keycode key)
{
    std::cout << "Key down: " << key << std::endl;
}

void Raycaster::OnKeyUp(SDL_Keycode key)
{
    std::cout << "Key up: " << key << std::endl;
}

void Raycaster::DrawCenteredHorizontalLine(uint32_t y, uint32_t length)
{
    Framebuffer& framebuf = renderer_.GetFrameBuffer();

    const uint32_t start_pos = framebuf.width() / 2 - (length / 2);
    const uint32_t end_pos = start_pos + length;

    framebuf.DrawHorizontalLine(y, start_pos, end_pos, 0x00ff000000);
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


float Raycaster::RoundDownToMultipleOf(float to_round, int32_t multiple)
{
    int32_t next_int = floor(to_round);
    return (next_int / multiple) * multiple;
}

const float Raycaster::kInitialPosX = 96.0f;
const float Raycaster::kInitialPosY = 96.0f;
const float Raycaster::kInitialPosOrientationDeg = 90.0f;
const float Raycaster::kMovementUnitsPerSec = 64.0f;
