#pragma once

#include <SDL.h>
#include <GL/glew.h>

class RenderingLoop
{
public:
    RenderingLoop();
    void Run();

private:
    void InitRendering();

private:
    SDL_Window* window_;

    GLuint program_;
    GLuint vao_;
    GLuint vbo_;
};


