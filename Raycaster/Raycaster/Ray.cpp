#include "Ray.h"

Ray::Ray(const glm::vec2& origin)
    :origin_(origin),
    collided_(false)
{
}
