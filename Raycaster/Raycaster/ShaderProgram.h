#pragma once

#include <GL/glew.h>

#include <string>

class ShaderProgram
{
public:
    ShaderProgram();
    ShaderProgram(GLuint vert_shader_id_, GLuint frag_shader_id);

    GLuint GetId() const;

    void SetBool(const std::string& name, bool value);
    void SetFloat(const std::string& name, float value);
    void SetInt(const std::string& name, int value);

private:
    GLuint id_;
};

