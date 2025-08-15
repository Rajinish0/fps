#version 330 core

in vec2 texCoord;

in vec3 fragPos;
in vec3 normalC;

out vec4 fragcol;


uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform vec3 lightDir;
uniform bool hasSpec;

vec3 lightColor = vec3(1.0);

void main() {

	float ambientStrength = 0.3;
	float specularStrength = 0.5;

	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normalC);
	vec3 diff = normalize(lightPos - fragPos);

	float dotp = abs(dot(norm, diff));
	vec3 diffuse_vec = lightColor * dotp;

	vec3 viewDir = normalize(fragPos - cameraPos);
	// vec3 reflectDir = reflect(diff, norm);
	float spec = pow(abs(dot(viewDir, lightDir)), 32);
	vec3 specular = specularStrength * spec * lightColor; 

	vec3 result = (ambient + diffuse_vec)*texture(texture_diffuse1, texCoord).rgb;
	if (hasSpec){
		result += specular*texture(texture_specular1, texCoord).rgb;
	}

	fragcol = vec4(result, 1.0);


	// vec3 diff = normalize(lightPos - fragPos);
	// fragcol = texture(text, texCoord);
	// fragcol += texture(text, texCoord)*abs(dot(normalize(lightDir), diff))*0.5;
	// fragcol = vec4(1.0, 0.0, 0.0, 1.0);
}