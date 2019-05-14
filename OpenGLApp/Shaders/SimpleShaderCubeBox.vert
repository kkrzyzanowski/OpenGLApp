#version 330 core
layout (location = 0) in vec3 vPos;

out vec3 TexDir;


uniform mat4 projection;
uniform mat4 view;

float cubeMapScale = 80.0;

void main()
{
	TexDir = vPos;
     vec4 pos = projection * view * vec4(vPos* cubeMapScale, 1.0);
	 gl_Position =  pos.xyzw;
}