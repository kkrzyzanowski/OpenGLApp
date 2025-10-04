#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor = vec3(0.94, 0.74, 0.94);
uniform vec3 lightPosition = vec3(0.0, 10.0, 0.0);
uniform sampler2D diffuseTexture;

void main()
{
    vec3 color = texture(diffuseTexture, TexCoords).rgb;
    vec3 normal = normalize(Normal);

    vec3 ambient = 0.1 * color; // Ambient light contribution

    vec3 lightning = vec3(0.0);

    for(int i = 0; i < 1; ++i) {
        vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0)); // Example light direction
        float diff = max(dot(normal, lightDir), 0.0);
        lightning += diff * color * lightColor;

        // attenuation
        float distance = length(FragPos - lightPosition);
        float attenuation = 1.0 / (distance * distance);
        lightning *= attenuation;
    }
    vec3 result = ambient + lightning;

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);

    FragColor = vec4(result, 1.0);
}