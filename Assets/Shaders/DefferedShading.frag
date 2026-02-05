#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D pos;
uniform sampler2D normal;
uniform sampler2D albedoSpec;

struct Light{
    vec3 position;
    vec3 color;

    float linear;
    float quadratic;
    float radius;
};

uniform Light lights[2];
uniform vec3 viewPos;

void main()
{
    vec3 FragPos = texture(pos, TexCoords).rgb;
    if(length(FragPos) < 0.001)
        discard;
    
    vec3 Normal = normalize(texture(normal, TexCoords).rgb);
    vec3 Diffuse = texture(albedoSpec, TexCoords).rgb;
    float Specular = texture(albedoSpec, TexCoords).a;

    vec3 lightning = Diffuse * 0.1;
    vec3 viewDir = normalize(viewPos - FragPos);

    for(int i = 0; i < 2; ++i)
    {
        float dist = distance(lights[i].position, FragPos);
        if(dist < lights[i].radius)
        {
            // diffuse
            vec3 lightDir = normalize(lights[i].position - FragPos);
            vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].color;

            // specular
            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
            vec3 specular = lights[i].color * spec * Specular;

            float attenuation = 1.0 / (1.0 + lights[i].linear * dist + lights[i].quadratic * dist * dist);
            diffuse *= attenuation;
            specular *= attenuation;

            // add computed contribution (was previously a constant vec3(1.0))
            lightning += diffuse + specular;
        }
    }

    FragColor = vec4(lightning, 1.0);
}