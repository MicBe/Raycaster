#include "RenderingLoop.h"

#include "Program.h"
#include "Shader.h"

#include <GL/glew.h>

#include <exception>
#include <fstream>
#include <streambuf>

RenderingLoop::RenderingLoop()
    :window_(nullptr),
    program_(-1),
    vao_(-1),
    vbo_(-1)
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

    InitRendering();
}

void RenderingLoop::Run()
{
    SDL_Event event;

    bool quit = false;
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

        // Render

        glUseProgram(program_);

        glBindVertexArray(vao_);
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap
        SDL_GL_SwapWindow(window_);
    }
}

void RenderingLoop::InitRendering()
{
    {
        std::ifstream vertex_shader_src("vert.glsl");
        std::ifstream fragment_shader_src("frag.glsl");

        Shader vertex_shader(Shader::ShaderType::VertexShader, std::string(std::istreambuf_iterator<char>(vertex_shader_src), std::istreambuf_iterator<char>()));
        Shader frag_shader(Shader::ShaderType::FragmentShader, std::string(std::istreambuf_iterator<char>(fragment_shader_src), std::istreambuf_iterator<char>()));

        if (!vertex_shader.Compile())
            throw std::exception((std::string("Unable to compile vertex shader: ") + vertex_shader.GetLastError()).c_str());
        if (!frag_shader.Compile())
            throw std::exception((std::string("Unable to compile fragment shader: ") + frag_shader.GetLastError()).c_str());

        Program program(vertex_shader.GetId(), frag_shader.GetId());
        if (!program.Link())
            throw std::exception((std::string("Unable to compile fragment shader: ") + program.GetLastError()).c_str());

        program_ = program.GetId();
    }

    glGenBuffers(1, &vbo_);
    glGenVertexArrays(1, &vao_);

    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_); // Not saved into vao
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Not saved into vao

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
