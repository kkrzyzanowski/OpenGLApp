#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 v_FragPos;
out vec2 v_TexCoords;
out vec3 v_Normal;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;
//uniform bool inverseNormals = false;

void main()
{
    v_FragPos = vec3(model * vec4(position, 1.0));
    v_TexCoords = texCoord;

    vec3 n = normal;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    v_Normal = normalize(normalMatrix * n);
    gl_Position = projection * view * model * vec4(position, 1.0);
}