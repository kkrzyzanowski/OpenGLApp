float ShadowCalculation(vec4 fragPosLightSpace, sampler2D shadowMap)
 {
	// perspective divide
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// 0-1 range
	projCoords = projCoords * 0.5 + 0.5;
	// closest depth value from light perspective
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	// get depth of current fragment from light's perspective
	float bias = 0.1;
	float currentDepth = projCoords.z;
	//check whether current frag pos is in ShadowCalculation
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
	return shadow;
 }

 struct Material 
 {
	sampler2D diffuse;
	sampler2D specular;
	vec3 ambient;

	float shininess;
 };

struct Light
{
	vec3 lightPos;
	vec3 ambient; 
	vec3 diffuse;
	vec3 specular; // parameters for materials
	float constant; // to point light
	float linear;
	float quadratic;
};

 float LinearizeDepth(float depth, float near, float far)
 {
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far)/(far + near - z *(far - near));
 }