#version 330 core

in vec2 texCoord;
in vec3 fragPos;
in vec3 normalC;

out vec4 fragCol;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform vec3 color;

void main(){
    fragCol = vec4(color, 1.0);
    //fragCol = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}