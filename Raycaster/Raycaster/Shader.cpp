#include "Shader.h"

Shader::Shader(ShaderType shader_type, const std::string& source_code)
    : id_(-1),
    type_(shader_type),
    source_code_(source_code)
{
}

Shader::~Shader()
{
    glDeleteShader(id_);
}

bool Shader::Compile()
{
    id_ = glCreateShader(static_cast<GLuint>(type_));

    const char* sourcecode_ptr = source_code_.c_str();
    glShaderSource(id_, 1, &sourcecode_ptr, nullptr);
    glCompileShader(id_);

    int success;
    char infolog[512];
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id_, 512, NULL, infolog);
        last_error_ = infolog;
    }

    return success != 0;
}

GLuint Shader::GetId() const
{
    return id_;
}

const std::string& Shader::GetLastError() const
{
    return last_error_;
}

