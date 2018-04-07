#pragma once

#include <glm/glm.hpp>

struct Ray
{
public:
    Ray(const glm::vec2& origin);

    glm::vec2 origin_;
    glm::vec2 dest_;
    bool collided_;
};

