#version 330 core 
 
 layout(location = 0) out vec4 color;

 in vec2 v_TexCoord;
 in vec3 FragPos;
 in vec3 Normal;

 uniform vec4 u_color;
 uniform sampler2D u_texture;
 uniform vec3 lightPos;
 uniform vec3 sunLight;
 uniform vec3 skyLight;

 void main()
 {
	float ambientStrength = 0.01;
	vec3 ambient = ambientStrength * sunLight * skyLight;

	vec3 norm = normalize(Normal);
	vec3 lightVec = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightVec), 0.0);
	vec3 diffuse = diff * sunLight * skyLight;

	vec4 texColor = texture(u_texture, v_TexCoord); 
 	color = u_color * texColor * vec4(diffuse + ambient, 1.0); 
 };