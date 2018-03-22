#pragma once

#include <cstdint>

class Camera
{
public:
    Camera(float position_x, float position_y, int32_t orientation_deg,
           int32_t fov, int32_t height, float units_per_sec);

    void GoForward(int32_t time_elapsed);
    void GoBackward(int32_t time_elapsed);
    void RotateLeft(int32_t time_elapsed);
    void RotateRight(int32_t time_elapsed);

    float position_x() const;
    float position_y() const;
    int32_t orientation_deg() const;
    int32_t fov() const;
    int32_t height();

private:
    float position_x_;
    float position_y_;
    int32_t orientation_deg_;
    int32_t fov_;
    int32_t height_;

    float units_per_sec_;
};

