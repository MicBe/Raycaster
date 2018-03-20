#pragma once

#include "Framebuffer.h"
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
    virtual void Update() override;

private:
    ShaderProgram textured_quad_shader_;
    GLuint vao_;
    GLuint vbo_;

    GLuint texture_;

    Framebuffer framebuffer_;

    static const int32_t kFramebufferWidth = 480;
    static const int32_t kFramebufferHeight = 640;
};

