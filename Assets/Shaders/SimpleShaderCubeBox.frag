#version 330 core
out vec4 FragColor;

in vec3 v_TexDir;
uniform samplerCube cubemap;

void main()
{
	FragColor = texture(cubemap, v_TexDir);
}


