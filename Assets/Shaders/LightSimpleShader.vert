#version 330 core	
layout (location = 0) in vec3 position;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

out vec3 FragPos;

uniform mat4 model;
void main()
{
	FragPos = vec3(model * vec4(position, 1.0));
	gl_Position = projection * view * model * vec4(position, 1.0);
}
