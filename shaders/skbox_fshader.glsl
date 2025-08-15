#version 330 core

in vec3 texCoord;

uniform samplerCube text;

out vec4 fcol;

void main() {
    fcol = texture(text, texCoord);    
    // fcol = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}