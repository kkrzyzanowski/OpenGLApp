#version 330 core

out vec4 FragColor; 

in vec3 v_FragPos;
in vec2 v_TexCoords;
in vec3 v_Normal;


struct SimpleLight {
    vec3 position;
    vec3 color;
};

uniform SimpleLight simpleLights[2];
uniform sampler2D diffuse;
uniform vec3 camPos;
uniform int lightsCount = 3;


void main()
{
    vec3 color = texture(diffuse, v_TexCoords).rgb;
    vec3 normal = normalize(v_Normal);

    float ambient = 0.0;

    vec3 lighting = vec3(0.0);

    for(int i = 0; i<2; i++)
    {
        vec3 lightDir = normalize(simpleLights[i].position - camPos);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuseColor = simpleLights[i].color * diff * color;

         float distance = length(v_FragPos - simpleLights[i].position);
         vec3 result = diffuseColor * (1.0/(distance * distance));
         lighting += result;
    }

    FragColor = vec4(lighting, 1.0);
}