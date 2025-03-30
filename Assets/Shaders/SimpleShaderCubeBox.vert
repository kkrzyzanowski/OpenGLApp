#version 330 core
layout (location = 0) in vec3 vPos;

out vec3 v_TexDir;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

void main()
{
	v_TexDir = vec3(vPos.x, vPos.y, -vPos.z);
    gl_Position = projection * view * vec4(vPos, 1.0);
	
}