#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 mvpResult;

out vec2 vTexCoords;

void main()
{
	vTexCoords = texCoord;
	gl_Position = mvpResult * vec4(position, 1.0);
}