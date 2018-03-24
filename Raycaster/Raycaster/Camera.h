#pragma once

#include <cstdint>
#include <utility>

class Camera
{
public:
    Camera(float position_x, float position_y, float orientation_deg,
           int32_t fov, int32_t height, float units_per_sec);

    void GoForward(int32_t time_elapsed);
    void GoBackward(int32_t time_elapsed);
    void RotateLeft(int32_t time_elapsed);
    void RotateRight(int32_t time_elapsed);

    float position_x() const;
    float position_y() const;
    float orientation_deg() const;
    int32_t fov() const;
    int32_t height();

private:
    std::pair<float, float> GetDeltaMove(int32_t time_elapsed) const;

    float position_x_;
    float position_y_;
    float orientation_deg_;
    int32_t fov_;
    int32_t height_;

    float movement_units_per_sec_;
    float rotation_angle_per_sec_;
};

