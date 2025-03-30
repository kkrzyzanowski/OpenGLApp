#version 330 core

#include "ShadowLibrary.glsl"


out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform Material material;
uniform Light light;

uniform vec3 camPos;
uniform vec3 sunLight;
uniform vec3 skyLight;

uniform sampler2D terrainTexture;
 uniform sampler2D shadowMap;

 float near =0.1;
 float far = 10;


void main()
{
	vec3 ambient = light.ambient * vec3(texture(terrainTexture, TexCoords)) * sunLight * skyLight * material.ambient;

	vec3 norm = normalize(Normal);
	float dist = length(light.lightPos - FragPos);
	//float attenaution = 1.0/(light.constant + light.linear * dist + light.quadratic * pow(dist, 2));
	vec3 lightVec = normalize(light.lightPos - FragPos);

	vec3 ambientLight = sunLight * skyLight;

	vec3 viewDir = normalize(camPos - FragPos);
	vec3 reflectDir = reflect(-lightVec, norm);

	float diff = max(dot(norm, lightVec), 0.0);

	vec3 diffuseColor = texture(terrainTexture, TexCoords).rgb;
	//vec4 diffuse = vec4(light.diffuse, 1.0) * diffuseColor * diff * vec4(sunLight,1.0) * vec4(skyLight, 1.0);
	vec3 diffuse = diffuseColor * sunLight * skyLight;

	float spec =  pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * vec3(texture(material.specular, TexCoords)); //* spec * sunLight;
//	
//	ambient *= attenaution;
//	diffuse *= attenaution;
//	specular *= attenaution;

	float depth = LinearizeDepth(gl_FragCoord.z, near, far)/far;

	// shadow
	float shadow = ShadowCalculation(FragPosLightSpace, shadowMap);
	vec3 lightning = (sunLight + (1.0 - shadow) * (diffuse + specular)) * diffuseColor;

	//for purpose 
 	FragColor = vec4(lightning, 1.0);
	//FragColor = vec4(vec3(texture(shadowMap, TexCoords)), 1.0);
}


