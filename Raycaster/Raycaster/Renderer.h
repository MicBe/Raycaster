#pragma once

#include "Framebuffer.h"
#include "ShaderProgram.h"

#include <GL/glew.h>

class Renderer
{
public:
    Renderer(int32_t framebuffer_width, int32_t framebuffer_height);

    void Init();
    void Render();
    
    Framebuffer& GetFrameBuffer();
    const Framebuffer& GetFrameBuffer() const;

private:
    Framebuffer framebuffer_;
    ShaderProgram textured_quad_shader_;

    GLuint vao_;
    GLuint vbo_;
    GLuint texture_;
};

