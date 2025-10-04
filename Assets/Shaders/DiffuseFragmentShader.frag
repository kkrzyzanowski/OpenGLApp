#version 330 core 
 
#include "ShadowLibrary.glsl"

 layout(location = 0) out vec4 Color;

 in vec2 TexCoord;
 in vec3 FragPos;
 in vec3 Normal;
 in vec4 FragPosLightSpace;

 uniform Material material;
 uniform sampler2D shadowMap;
 uniform Light light;

 uniform vec3 viewPos;
 uniform vec3 camPos;
 uniform vec3 sunLight;
 uniform vec3 skyLight;

// shadow variable maybe to implement

 float near =0.1;
 float far = 10;

 void main()
 {
	vec3 diffuseColor = texture(material.diffuse, TexCoord).rgb;

	vec3 norm = normalize(Normal);
	float dist = length(light.lightPos - FragPos);
	//float attenaution = 1.0/(light.constant + light.linear * dist + light.quadratic * pow(dist, 2));
	vec3 lightVec = normalize(light.lightPos - FragPos);
	float diff = max(dot(norm, lightVec), 0.0);

	vec3 diffuse = diffuseColor * sunLight * skyLight;

	vec3 viewDir = normalize(camPos - FragPos);
	vec3 reflectDir = reflect(-lightVec, norm);
	float spec =  pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * texture(material.specular, TexCoord).rgb;;

	// shadow
	float shadow = ShadowCalculation(FragPosLightSpace, shadowMap);
	vec3 lightining = (sunLight + (1.0 - shadow) * (diffuse + specular)) * diffuseColor; 
   
 	Color = vec4(lightining, 1.0);
	//color = vec4(vec3(texture(shadowMap, TexCoord).r), 1.0);
 };