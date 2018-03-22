#include "Renderer.h"

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <fstream>
#include <streambuf>

Renderer::Renderer()
    : framebuffer_(kFramebufferWidth, kFramebufferHeight),
    textured_quad_shader_(),
    vao_(-1),
    vbo_(-1),
    texture_(-1)
{
}

void Renderer::Init()
{
    std::ifstream vertex_shader_src("vert.glsl");
    std::ifstream fragment_shader_src("frag.glsl");

    Shader vertex_shader(Shader::ShaderType::VertexShader, std::string(std::istreambuf_iterator<char>(vertex_shader_src), std::istreambuf_iterator<char>()));
    Shader frag_shader(Shader::ShaderType::FragmentShader, std::string(std::istreambuf_iterator<char>(fragment_shader_src), std::istreambuf_iterator<char>()));

    if (!vertex_shader.Compile())
        throw std::exception((std::string("Unable to compile vertex shader: ") + vertex_shader.GetLastError()).c_str());
    if (!frag_shader.Compile())
        throw std::exception((std::string("Unable to compile fragment shader: ") + frag_shader.GetLastError()).c_str());

    textured_quad_shader_ = ShaderProgram(vertex_shader.GetId(), frag_shader.GetId());

    glGenBuffers(1, &vbo_);
    glGenVertexArrays(1, &vao_);

    // Includes tex coords
    constexpr float fullscreen_quad[] = {
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Top left
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom left
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Top right
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Top right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom left
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f // Bottom right
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fullscreen_quad), fullscreen_quad, GL_STATIC_DRAW);

    glBindVertexArray(vao_);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0); // Coords
    glEnableVertexAttribArray(1); // Tex coords

                                  /*int x, y, channels;
                                  stbi_set_flip_vertically_on_load(1);
                                  stbi_uc* image = stbi_load("textures/test_borders.png", &x, &y, &channels, STBI_rgb);*/

    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, kFramebufferWidth, kFramebufferHeight, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, framebuffer_.Get());

    /*stbi_image_free(image);*/

    glUseProgram(textured_quad_shader_.GetId());
    textured_quad_shader_.SetInt("TexCoord", 0);
}

void Renderer::Render()
{
    /*glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);*/

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, kFramebufferWidth, kFramebufferHeight, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, framebuffer_.Get());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_);

    glUseProgram(textured_quad_shader_.GetId());

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::Update()
{
    uint8_t red = 0, green = 0, blue = 255;

    framebuffer_.DrawHorizontalLine(320, 10, 24, (red << 24) | (green << 16) | (blue << 8));
}

