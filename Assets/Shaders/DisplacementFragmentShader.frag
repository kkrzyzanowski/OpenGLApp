#version 330 core

in vec2 v_TexCoord;
in vec3 v_FragPos;
in vec3 v_TangentLightPos;
in vec3 v_TangentViewPos;
in vec3 v_TangentFragPos;

out vec4 FragColor; 

uniform sampler2D diffuse;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform float heightScale = 0.1;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main()
{

	vec3 lightDir = normalize(v_TangentLightPos - v_TangentFragPos);
	vec3 viewDir = normalize(v_TangentViewPos - v_TangentFragPos);
	
	vec2 texCoords = ParallaxMapping(v_TexCoord, viewDir);
	if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
        discard;


	vec3 texColor = texture(diffuse, texCoords).rgb;
	vec3 ambient = 0.7 * texColor;
//	if(texColor.a < 0.1)
//		discard;
	vec3 normal = texture(normalMap, texCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuseVal = diff * texColor;

	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
	vec3 specular = vec3(0.4) * spec;
	FragColor = vec4(ambient + diffuseVal + specular, 1.0);
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
	const float minLayers = 8.0;
	const float maxLayers = 32.0;

	float numLayers = mix(maxLayers, minLayers, max(dot(vec3(0.0, 0.0, 1.0), viewDir), 0.0));
//	const float numLayers = 10;
	float layerDepth = 1.0/ numLayers;
	float currentDepth = 0.0f;

	vec2 P = viewDir.xy * heightScale;
	vec2 deltaTexCoords = P/numLayers;

	vec2 currentTexCoords = texCoords;
	float currentDepthMapValue = texture(depthMap, currentTexCoords).r;

	while(currentDepth < currentDepthMapValue)
	{
		currentTexCoords -= deltaTexCoords;
		currentDepthMapValue = texture(depthMap, currentTexCoords).r;
		currentDepth += layerDepth;
	}
	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	float afterDepth = currentDepthMapValue - layerDepth;
	float beforeDepth = texture(depthMap, prevTexCoords).r - currentDepth + layerDepth;

	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;
}
