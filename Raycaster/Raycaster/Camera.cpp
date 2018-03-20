#include "Camera.h"

Camera::Camera()
{
    // Camera is in the middle, bottom of the map, looking up the map
    position_x_ = 5.0f;
    position_y_ = 10.0f;
    orientation_ = 90.0f;
    fov_ = 60;
}
