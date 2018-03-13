#include "RenderingLoop.h"

#include "ConsoleFpsCounter.h"
#include "IRenderable.h"

#include <GL/glew.h>

#include <exception>
#include <vector>

RenderingLoop::RenderingLoop(std::unique_ptr<IRenderable> renderable)
    : renderable_(std::move(renderable)),
    window_(nullptr)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::exception("Unable to init SDL");

    static const int WINDOW_SIZE_X = 800;
    static const int WINDOW_SIZE_Y = 600;
    window_ = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window_)
        throw std::exception("Unable to create window");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    auto context = SDL_GL_CreateContext(window_);
    if (!context)
        throw std::exception("Unable to create OpenGL context");

    glewExperimental = GL_TRUE;
    GLenum glew_init_res = glewInit();
    if (glew_init_res != GLEW_OK)
        throw std::exception("Glew failed to initialize");

    glViewport(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);
}

void RenderingLoop::Run()
{
    renderable_->Init();

    bool quit = false;

    SDL_Event event;
    ConsoleFpsCounter fps_counter;
    while (!quit)
    {
        // Process events
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_WINDOWEVENT)
            {
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    glViewport(0, 0, event.window.data1, event.window.data2);
                    break;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        renderable_->Render();
        SDL_GL_SwapWindow(window_);

        fps_counter.FrameFinished();
    }
}
