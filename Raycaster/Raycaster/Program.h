#pragma once

#include <GL/glew.h>

#include <string>

class Program
{
public:
    Program(GLuint vert_shader_id_, GLuint frag_shader_id);

    GLuint GetId() const;
    bool Link();
    const std::string& GetLastError();

private:
    GLuint id_;

    GLuint vert_shader_id_;
    GLuint frag_shader_id_;

    std::string last_error_;
};

