#include "Ray.h"

Ray::Ray(const glm::vec2& origin, const float angle)
    :origin_(origin),
    collided_(false),
    angle_(angle)
{
}
