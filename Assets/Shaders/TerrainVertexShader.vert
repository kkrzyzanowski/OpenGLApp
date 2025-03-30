#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out vec4 FragPosLightSpace;

const int val = 256;
layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;
uniform mat4 lightSpaceMatrix;
uniform vec3 offset[val];



void main()
{
	TexCoords = texCoord;
	FragPos = vec3(model * vec4(position, 1.0));
	Normal = transpose(inverse(mat3(model))) * normal;
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
	gl_Position = projection * view * model * vec4(position + offset[gl_InstanceID], 1.0);

}