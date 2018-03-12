#include "ShaderProgram.h"

#include <exception>

ShaderProgram::ShaderProgram()
    :id_(-1)
{
}

ShaderProgram::ShaderProgram(GLuint vert_shader_id, GLuint frag_shader_id)
    : id_(-1)
{
    id_ = glCreateProgram();

    glAttachShader(id_, vert_shader_id);
    glAttachShader(id_, frag_shader_id);
    glLinkProgram(id_);

    int success;
    char infolog[512];
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id_, 512, NULL, infolog);
        throw std::exception(infolog);
    }
}

GLuint ShaderProgram::GetId() const
{
    return id_;
}

void ShaderProgram::SetBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), static_cast<int>(value));
}

void ShaderProgram::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void ShaderProgram::SetInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}
