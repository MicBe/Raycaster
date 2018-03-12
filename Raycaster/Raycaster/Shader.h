#pragma once

#include <GL/glew.h>

#include <string>

class Shader
{
public:
    enum class ShaderType
    {
        VertexShader = GL_VERTEX_SHADER,
        FragmentShader = GL_FRAGMENT_SHADER,
    };

public:
    Shader(ShaderType shader_type, const std::string& source_code);
    ~Shader();

    bool Compile();
    GLuint GetId() const;
    const std::string& GetLastError() const;

protected:
    GLuint id_;
    ShaderType type_;
    std::string source_code_;
    std::string last_error_;
};

