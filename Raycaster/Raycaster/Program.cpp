#include "Program.h"


Program::Program(GLuint vert_shader_id, GLuint frag_shader_id)
    : id_(-1),
    vert_shader_id_(vert_shader_id),
    frag_shader_id_(frag_shader_id)
{
}

GLuint Program::GetId() const
{
    return id_;
}

bool Program::Link()
{
    id_ = glCreateProgram();

    glAttachShader(id_, vert_shader_id_);
    glAttachShader(id_, frag_shader_id_);
    glLinkProgram(id_);

    int success;
    char infolog[512];
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id_, 512, NULL, infolog);
        last_error_ = infolog;
    }

    return success != 0;
}

const std::string& Program::GetLastError()
{
    return last_error_;
}
