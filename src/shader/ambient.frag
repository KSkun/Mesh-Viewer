#version 330 core

in vec3 worldPos;
in vec3 normal;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D texDiffuse;

void main() {
    FragColor = texture(texDiffuse, vec2(texCoord.x, texCoord.y));
}