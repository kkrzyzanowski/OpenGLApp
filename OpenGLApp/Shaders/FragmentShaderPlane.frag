#version 330 core 
 
 layout(location = 0) out vec4 color;

 in vec2 v_TexCoord;

 uniform vec4 u_color;
 uniform sampler2D u_texture;
 uniform vec3 sunLight;
 uniform vec3 skyLight;

 void main()
 {
	vec4 texColor = texture(u_texture, v_TexCoord); 
 	color = u_color * texColor * vec4(sunLight * skyLight, 1.0); 
 };