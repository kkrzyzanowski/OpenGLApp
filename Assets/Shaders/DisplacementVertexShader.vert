#version 330 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec2 v_TexCoord;
out vec3 v_FragPos;
out vec3 v_TangentLightPos;
out vec3 v_TangentViewPos;
out vec3 v_TangentFragPos;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	v_FragPos = vec3(model * vec4(position, 1.0));
	v_TexCoord = texCoord;

	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 T = normalize(vec3(normalMatrix * tangent));
	vec3 N = normalize(vec3(normalMatrix * normal));

	T = normalize(T - dot(T,N) * N);
	vec3 B = cross(T, N);
	mat3 TBN = transpose(mat3(T, B, N));

	v_TangentLightPos = TBN * lightPos;
	v_TangentViewPos = TBN * camPos;
	v_TangentFragPos = TBN * v_FragPos;

	gl_Position = projection * view * vec4(v_FragPos, 1.0);
};