#version 330 core
layout(location = 0) in vec3 pos;


out vec3 texCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
    texCoord = pos;
	vec4 p = proj*view*model*vec4(pos, 1.0);
    gl_Position = p;
}