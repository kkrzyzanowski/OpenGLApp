#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D pos;
uniform sampler2D normal;
uniform sampler2D albedoSpec;
uniform sampler2D ssao;

struct Light{
    vec3 position;
    vec3 color;
    float linear;
    float quadratic;
}

uniform Light lights[2];

void main()
{
    vec3 FragPos = texture(pos, TexCoords).rgb;
    if(length(FragPos) < 0.001)
        discard;
    vec3 Normal = normalize(texture(normal, TexCoords).rgb);
    vec3 Diffuse = texture(albedoSpec, TexCoords).rgb;
    float Specular = texture(albedoSpec, TexCoords).a;
    float AmbientOcclusion = texture(ssao, TexCoords).r;

    vec3 lightning = Diffuse * 0.1 * AmbientOcclusion;
    vec3 viewDir = normalize(-FragPos);

    for(int i = 0; i < 2; ++i)
    {
        vec3 lightDir = normalize(lights[i].position - FragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);

        vec3 diffuse += max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].color;
        vec3 specular += pow(max(dot(Normal, halfwayDir), 0.0), 16.0) * Specular * lights[i].color;
        
        float dist = distance(lights[i].position, FragPos);
        float attenuation = 1.0 / (1.0 + lights[i].linear * dist + lights[i].quadratic * dist * dist);
        diffuse *= attenuation;
        specular *= attenuation;
        lightning += diffuse + specular;
    }

    FragColor = vec4(lightning, 1.0);
}
