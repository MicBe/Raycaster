#pragma once

#include "IRenderable.h"
#include "ShaderProgram.h"

#include <GL/glew.h>

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

    GLuint texture_;
};

