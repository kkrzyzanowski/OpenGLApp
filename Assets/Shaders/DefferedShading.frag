#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedoSpec;

struct Light{
    vec3 position;
    vec3 color;

    float linear;
    float quadratic;
    float radius;
};

uniform Light lights[4];
uniform vec3 camPos;

void main()
{
    vec3 FragPos = texture(position, TexCoords).rgb;
    vec3 Normal = texture(normal, TexCoords).rgb;
    vec3 Diffuse = texture(albedoSpec, TexCoords).rgb;
    float Specular = texture(albedoSpec, TexCoords).a;

    vec3 lightning = Diffuse * 0.1;
    vec3 viewDir = normalize(camPos - FragPos);

    for(int i=0; i<4; ++i)
    {
        float dist = distance(lights[i].position, FragPos);
        if(dist < lights[i].radius)
        {
            //diffuse
            vec3 lightDir = normalize(lights[i].position - FragPos);
            vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].color;

            //specular
            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
            vec3 specular = lights[i].color * spec * Specular;    

            float attenuation = 1.0 / (1.0 + lights[i].linear * dist + lights[i].quadratic * dist * dist);
            diffuse *= attenuation;
            specular *= attenuation;
            lightning += diffuse + specular;       
        }
    }

    FragColor = vec4(lightning, 1.0);
}