#pragma once

#include "Framebuffer.h"
#include "ShaderProgram.h"

#include <GL/glew.h>


class Renderer
{
public:
    Renderer();

    void Init();
    void Render();
    void Update();

private:
    Framebuffer framebuffer_;
    ShaderProgram textured_quad_shader_;

    GLuint vao_;
    GLuint vbo_;
    GLuint texture_;

private:
    static const int32_t kFramebufferWidth = 480;
    static const int32_t kFramebufferHeight = 640;
};

