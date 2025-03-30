#version 330 core 
 
 layout(location = 0) out vec4 FragColor;

 in vec2 v_TexCoord;

uniform vec4 color;
uniform sampler2D diffuse;

 void main()
 {
	vec4 texColor = texture(diffuse, v_TexCoord); 
 	FragColor = color * texColor; 
 };