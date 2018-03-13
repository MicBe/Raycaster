#pragma once

#include "IRenderable.h"
#include "ShaderProgram.h"

#include <GL/glew.h>

#include <array>

class Raycaster : public IRenderable
{
public:
    Raycaster();

    virtual void Init() override;
    virtual void Render() override;

private:
    ShaderProgram textured_quad_shader_;
    GLuint vao_;
    GLuint vbo_;

    std::array<unsigned char, 800 * 600 * 3> framebuffer_;

    GLuint texture_;
};

