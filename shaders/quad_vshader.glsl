#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tCoord;
layout(location = 2) in vec3 normalCoord;

out vec2 texCoord;
out vec3 normalC;
out vec3 fragPos;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
	gl_Position = proj*view*model*vec4(pos.x, pos.y, 0.0, 1.0);
	fragPos = (model*vec4(pos.x, pos.y, 0.0, 1.0)).xyz;
	normalC = normalize(mat3(transpose(inverse(model)))*normalCoord);
	texCoord = tCoord;
}