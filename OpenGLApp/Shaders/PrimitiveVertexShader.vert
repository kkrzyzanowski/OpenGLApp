#version 330 core	

in vec3 position;

uniform mat4 mvpResult;
void main()
{
	gl_Position = mvpResult * vec4(position, 1.0);
}
