#version 330 core
layout (location = 0) in vec3 vPos;

out vec3 TexDir;


uniform mat4 projection;
uniform mat4 view;


void main()
{
	TexDir = vPos;
    gl_Position = projection * view * vec4(vPos, 1.0);
	
}