#include "Camera.h"

Camera::Camera(float position_x, float position_y, int32_t orientation_deg,
               int32_t fov, int32_t height, float units_per_sec)
    :position_x_(position_x),
    position_y_(position_y),
    orientation_deg_(orientation_deg),
    fov_(fov),
    height_(height),
    units_per_sec_(units_per_sec)
{
    position_x_ = 1.0f;
    position_y_ = 10.0f;
    orientation_deg_ = 60;
    fov_ = 60;
}

void Camera::GoForward(int32_t time_elapsed)
{
    // TODO
}

void Camera::GoBackward(int32_t time_elapsed)
{
    // TODO
}

void Camera::RotateLeft(int32_t time_elapsed)
{
    // TODO
}

void Camera::RotateRight(int32_t time_elapsed)
{
    // TODO
}

float Camera::position_x() const
{
    return position_x_;
}

float Camera::position_y() const
{
    return position_y_;
}

int32_t Camera::orientation_deg() const
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
