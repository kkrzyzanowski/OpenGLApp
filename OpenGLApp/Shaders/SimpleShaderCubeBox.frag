#version 330 core
out vec4 FragColor;

in vec3 TexDir;
uniform samplerCube cubemap;

void main()
{
	FragColor = texture(cubemap, TexDir);
}


