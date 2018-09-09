#pragma once

#include <glm/glm.hpp>

struct Ray
{
public:
    Ray(const glm::vec2& origin, const float angle);

    glm::vec2 dest_;
    bool collided_;

    const glm::vec2 origin_;
    const float angle_;
};

