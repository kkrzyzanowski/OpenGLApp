#version 330 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;


void main()
{
	FragPos = vec3(model * vec4(position, 1.0));
	gl_Position = projection * view * vec4(FragPos, 1.0);
	v_TexCoord = texCoord;
	Normal = normal;
};
