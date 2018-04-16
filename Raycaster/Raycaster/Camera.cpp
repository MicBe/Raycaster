#include "Camera.h"

#include <glm/glm.hpp>

Camera::Camera(float position_x, float position_y, float orientation_deg,
               int32_t fov, int32_t height, float units_per_sec)
    :position_x_(position_x),
    position_y_(position_y),
    orientation_deg_(orientation_deg),
    fov_(fov),
    height_(height),
    movement_units_per_sec_(units_per_sec),
    rotation_angle_per_sec_(180.0f)
{
}

void Camera::GoForward(int32_t time_elapsed)
{
    auto delta = GetDeltaMove(time_elapsed);
    position_x_ += delta.first;
    position_y_ += delta.second;
}

void Camera::GoBackward(int32_t time_elapsed)
{
    auto delta = GetDeltaMove(time_elapsed);
    position_x_ -= delta.first;
    position_y_ -= delta.second;
}

void Camera::RotateLeft(int32_t time_elapsed)
{
    orientation_deg_ += static_cast<float>(time_elapsed / 1000.0f) * rotation_angle_per_sec_;
    if (orientation_deg_ >= 360.0f)
        orientation_deg_ -= 360.0f;
}

void Camera::RotateRight(int32_t time_elapsed)
{
    orientation_deg_ -= static_cast<float>(time_elapsed / 1000.0f) * rotation_angle_per_sec_;
    if (orientation_deg_ < 0.0f)
        orientation_deg_ += 360.0f;
}

float Camera::position_x() const
{
    return position_x_;
}

float Camera::position_y() const
{
    return position_y_;
}

float Camera::orientation_deg() const
{
    return orientation_deg_;
}

int32_t Camera::fov() const
{
    return fov_;
}

int32_t Camera::height()
{
    return height_;
}

std::pair<float, float> Camera::GetDeltaMove(int32_t time_elapsed) const
{
    const float move_coeff = movement_units_per_sec_ * static_cast<float>(time_elapsed / 1000.0f);

    float delta_x = cos(glm::radians(orientation_deg_)) * move_coeff;
    float delta_y = -sin(glm::radians(orientation_deg_)) * move_coeff;

    return std::make_pair(delta_x, delta_y);
}
