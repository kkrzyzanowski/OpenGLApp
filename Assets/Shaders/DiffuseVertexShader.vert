#version 330 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;
out vec4 FragPosLightSpace;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;
uniform mat4 lightSpaceMatrix;


void main()
{
	FragPos = vec3(model * vec4(position, 1.0));
	TexCoord = texCoord;
	Normal = mat3(transpose(inverse(model)))*normal;
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
	gl_Position = projection * view * model * vec4(position, 1.0);
};
