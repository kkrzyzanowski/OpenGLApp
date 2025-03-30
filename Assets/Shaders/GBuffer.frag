#version 330 core
layout (location = 0) out vec3 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec4 albedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D diffuse;
uniform sampler2D specular;

void main()
{
    position = FragPos;
    normal = normalize(Normal);
    albedoSpec.rgb = texture(diffuse, TexCoords).rgb;
    albedoSpec.a = texture(specular, TexCoords).a;
}