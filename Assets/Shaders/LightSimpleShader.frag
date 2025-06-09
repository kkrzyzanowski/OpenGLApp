#version 330 core
layout (location = 0) out vec4 FragColor;

in vec3 FragPos;
uniform vec3 lightColor = vec3(0.94, 0.74, 0.94);

void main()
{
	FragColor = vec4(lightColor, 1.0);
}