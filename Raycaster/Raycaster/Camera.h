#pragma once

#include <cstdint>

class Camera
{
public:
    Camera();

private:
    float position_x_;
    float position_y_;
    float orientation_;
    int32_t fov_;
};

