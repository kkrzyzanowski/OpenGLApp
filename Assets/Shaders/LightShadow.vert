#version 330 core
layout (location = 0) in vec3 lPos;

const int val = 256;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;
uniform vec3 offset[val];

void main()
{
	gl_Position = lightSpaceMatrix * model * vec4(lPos + offset[gl_InstanceID], 1.0);
}