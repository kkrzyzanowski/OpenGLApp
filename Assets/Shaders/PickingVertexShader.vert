#version 330 core	

in vec3 position;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;
void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
}
