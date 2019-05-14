#version 330 core 
 
 layout(location = 0) out vec4 color;

 in vec2 v_TexCoord;
 in vec3 FragPos;
 in vec3 Normal;

 struct Material 
 {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normalMap;
	vec3 ambient;

	float shininess;
 };

 struct Light
 {
	vec3 lightPos;

	vec3 camPos;
	vec3 direction;
	float cutOff;


	vec3 ambient; 
	vec3 diffuse;
	vec3 specular; // parameters for materials

	float constant; // to point light
	float linear;
	float quadratic;
 };

 uniform Material material;
 uniform Light light;

 uniform vec3 sunLight;
 uniform vec3 skyLight;
 uniform vec3 camPos;

 float near =0.1;
 float far = 10;

 float LinearizeDepth(float depth)
 {
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far)/(far + near - z *(far - near));
 }

 void main()
 {
	
	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoord)) * sunLight * skyLight * material.ambient;

	vec3 norm = normalize(Normal);
	float dist = length(light.lightPos - FragPos);
	float attenaution = 1.0/(light.constant + light.linear * dist + light.quadratic * pow(dist, 2));
	vec3 lightVec = normalize(light.lightPos - FragPos);


	vec3 viewDir = normalize(camPos - FragPos);
	vec3 reflectDir = reflect(-lightVec, norm);

	float diff = max(dot(norm, lightVec), 0.0);

	vec4 diffuseColor = texture(material.diffuse, v_TexCoord);
	if(diffuseColor.a <= 0.01)
		discard;
	vec4 diffuse = vec4(light.diffuse, 1.0) * diffuseColor * diff * vec4(sunLight,1.0) * vec4(skyLight, 1.0);

	float spec =  pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * vec3(texture(material.specular, v_TexCoord)) * spec * sunLight;
	
	ambient *= attenaution;
	diffuse *= attenaution;
	specular *= attenaution;

	//float depth = LinearizeDepth(gl_FragCoord.z)/far;
 	color = diffuse + vec4(ambient + specular, 1.0); 
 };