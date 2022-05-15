#version 330 core

in vec3 worldPos;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D texDiffuse;

void main() {
    gl_FragColor = texture(texDiffuse, vec2(texCoord.x, 1.0 - texCoord.y));
}