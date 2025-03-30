#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec2 TexCoords;
in vec3 Normal;
in vec2 FragPos;


uniform vec3 lightColor = vec3(0.94, 0.74, 0.94);

void main()
{
	FragColor = vec4(lightColor, 1.0);
	float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
	if(brightness > 1.0)
		BrightColor = FragColor;
	else
		BrightColor = vec4(0.0, 0.0, 0.0, 1.0);

}