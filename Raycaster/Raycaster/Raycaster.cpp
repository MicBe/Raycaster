#include "Raycaster.h"

#include <glm/glm.hpp>
#include <SDL.h>

#include <iostream>

Raycaster::Raycaster()
    :camera_(glm::vec2(kInitialPosX, kInitialPosY),
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
    std::cout << "Camera x: " << camera_.position().x << std::endl;
    std::cout << "Camera y: " << camera_.position().y << std::endl;
    std::cout << "Orientation: " << camera_.orientation_deg() << std::endl;
    
    renderer_.GetFrameBuffer().Fill(0);

    const float increment = static_cast<float>(camera_.fov()) / static_cast<float>(kFramebufferHeight);
    float ray_angle = camera_.orientation_deg() - (camera_.fov() / 2);

    for (int32_t ray_index = 0; ray_index < kFramebufferHeight; ++ray_index)
    {
		Ray ray(camera_.position(), ray_angle);
		CastRay(ray);

		//DrawStripe(ray_index, ((float)ray_index / kFramebufferHeight) * kFramebufferWidth);

		if (ray.collided_)
		{
			const float distorted_dist = glm::sqrt(glm::pow(ray.dest_.x - ray.origin_.x, 2) + glm::pow(ray.dest_.y - ray.origin_.y, 2));
			const float corrected_dist = glm::cos(glm::radians(glm::abs(camera_.orientation_deg() - ray_angle))) * distorted_dist;
			const float dist_cam_to_proj_plane = 554.256f;

			// Draw wall
//			int32_t stripe_length = (static_cast<float>(world_.units_per_block()) / corrected_dist) * dist_cam_to_proj_plane;

			DrawStripe(ray_index, glm::clamp((static_cast<float>(world_.units_per_block()) / corrected_dist) * dist_cam_to_proj_plane, 0.0f, 480.0f));
		}

        ray_angle += increment;
    }
}

void Raycaster::CastRay(Ray& ray)
{
	bool ray_facing_up = ray.angle_ > 0.0f && ray.angle_ <= 180.0f;
	bool ray_facing_left = ray.angle_ > 90.0f && ray.angle_ <= 270.0f;

	const int32_t horiz_increment_x = static_cast<float>(world_.units_per_block()) / glm::tan(glm::radians(ray.angle_));
	const int32_t horiz_increment_y = world_.units_per_block() * (ray_facing_up ? -1 : 1);

	int32_t horiz_pos_x = ray.origin_.x;
	int32_t horiz_pos_y = ray.origin_.y;

	int32_t horiz_intersect_x = 0;
	int32_t horiz_intersect_y = 0;

	if (ray_facing_up)
		horiz_intersect_y = RoundDownToMultipleOf(horiz_pos_y, kUnitsPerBlock) - 1; // Y intersect is slightly above the line
	else
		horiz_intersect_y = RoundDownToMultipleOf(horiz_pos_y, kUnitsPerBlock) + world_.units_per_block(); // Y intersect is slightly below the line

	horiz_intersect_x = horiz_pos_x + ((horiz_pos_y - horiz_intersect_y) / glm::tan(glm::radians(ray.angle_)));

	// Checking for horizontal intersections
	horiz_pos_x = horiz_intersect_x;
	horiz_pos_y = horiz_intersect_y;
	bool collided_horiz = false;

	do
	{
		if (world_.IsInsideBlock(horiz_pos_x, horiz_pos_y))
			collided_horiz = true;
		else
		{
			if (world_.IsInsideWorld(horiz_pos_x, horiz_pos_y))
			{
				horiz_pos_x += horiz_increment_x;
				horiz_pos_y += horiz_increment_y;
			}
			else
				break;
		}
	} while (!collided_horiz);

	const int32_t vert_increment_x = world_.units_per_block() * ray_facing_left ? -1 : 1;
	const int32_t vert_increment_y = static_cast<float>(world_.units_per_block()) * glm::tan(glm::radians(ray.angle_));

	int32_t vert_pos_x = ray.origin_.x;
	int32_t vert_pos_y = ray.origin_.y;

	int32_t vert_intersect_x = 0;
	int32_t vert_intersect_y = 0;

	// Checking for vertical intersections
	if (ray_facing_left)
		vert_intersect_x = RoundDownToMultipleOf(vert_pos_x, world_.units_per_block()) - 1;
	else
		vert_intersect_x = RoundDownToMultipleOf(vert_pos_x, world_.units_per_block()) + world_.units_per_block();

	vert_intersect_y = vert_pos_y + (glm::tan(glm::radians(ray.angle_)) * (vert_pos_x - vert_intersect_x));

	vert_pos_x = vert_intersect_x;
	vert_pos_y = vert_intersect_y;
	bool collided_vert = false;
	
	do
	{
		if (world_.IsInsideBlock(vert_pos_x, vert_pos_y))
			collided_vert = true;
		else
		{
			if (world_.IsInsideWorld(vert_pos_x, vert_pos_y))
			{
				vert_pos_x += vert_increment_x;
				vert_pos_y += vert_increment_y;
			}
			else
				break;
		}

	} while (!collided_vert);

	if (collided_horiz || collided_vert)
	{
		ray.collided_ = true;

		int32_t dist_intersect_horiz = glm::sqrt(glm::pow(ray.origin_.x - horiz_pos_x, 2) + glm::pow(ray.origin_.y - horiz_pos_y, 2));
		int32_t dist_intersect_vert = glm::sqrt(glm::pow(ray.origin_.x - vert_pos_x, 2) + glm::pow(ray.origin_.y - vert_pos_y, 2));

		if (dist_intersect_horiz < dist_intersect_vert)
		{
			//assert(dist_intersect_horiz >= 1.0f);
			ray.dest_ = glm::vec2(horiz_pos_x, horiz_pos_y);
		}
		else
		{
			//assert(dist_intersect_vert >= 1.0f);
			ray.dest_ = glm::vec2(vert_pos_x, vert_pos_y);
		}
	}
}

void Raycaster::DrawStripe(uint32_t y, uint32_t length)
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


int32_t Raycaster::RoundDownToMultipleOf(float to_round, int32_t multiple)
{
    float floored = glm::floor(to_round / static_cast<float>(multiple));
    return floored * multiple;
}

const float Raycaster::kInitialPosX = 320.0f;
const float Raycaster::kInitialPosY = 320.0f;
const float Raycaster::kInitialPosOrientationDeg = 0.0f;
const float Raycaster::kMovementUnitsPerSec = 64.0f;
