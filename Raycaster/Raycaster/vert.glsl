#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 texCoords;

out vec2 TexCoord;

void main()
{
	TexCoord = vec2(texCoords.x, texCoords.y);
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}
