#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D bloomTexture;
uniform bool horizontal = true;
uniform float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{
	//FragColor = vec4(1.0, 1.0, 1.0, 1.0);

	vec2 tex_offset = 1.0 / textureSize(bloomTexture, 0);
	vec3 result = texture(bloomTexture, TexCoords).rgb * weight[0];


		for(int i=1;i<5; ++i)
		{
			result += texture(bloomTexture, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
			result += texture(bloomTexture, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
		}
	
	// for(int i=1;i<5; ++i)
	// 	{
	// 		result += texture(bloomTexture, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
	// 		result += texture(bloomTexture, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
	// 	}
	

	FragColor = vec4(result, 1.0);
}