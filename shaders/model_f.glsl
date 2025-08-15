#version 330 core

in vec2 texCoord;
in vec3 fragPos;
in vec3 normalC;

out vec4 fragCol;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform vec3 camPos;
uniform vec3 lightPos;

vec3 lightColor = vec3(1.0);

float ambientStrength = 0.3;
float specularStrength = 0.5;

void main(){

    vec3 ambient = ambientStrength * lightColor;
    vec3 diff = normalize(lightPos - fragPos);

	float dotp = max(dot(normalC, diff), 0);
	vec3 diffuse_vec = lightColor * dotp;

    vec3 viewDir = normalize(camPos - fragPos);
	vec3 reflectDir = reflect(diff, normalC);
	float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
	vec3 specular = specularStrength * spec * lightColor; 

    // vec3 result = specular * texture(texture_specular1, texCoord).rgb;
    vec3 result = (ambient + diffuse_vec)*texture(texture_diffuse1, texCoord).rgb;
    result += specular * texture(texture_specular1, texCoord).rgb;
    fragCol = vec4(result, 1.0);
    // fragCol = vec4(0.5, 0.1, 0.0, 1.0);
}