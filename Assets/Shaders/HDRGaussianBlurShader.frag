#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloom;

uniform float exposure = 0.0;
void main()
{
	const float gamma = 2.2;
	vec3 hdrColor = texture(scene, TexCoords).rgb;
	vec3 blurColor = texture(bloom, TexCoords).rgb;
	hdrColor += blurColor;
	vec3 result = vec3(1.0, 1.0, 1.0) - exp(-hdrColor * exposure);

	result = pow(result, vec3(1.0/gamma));
	FragColor = vec4(result, 1.0);

}