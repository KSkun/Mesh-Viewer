#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 worldPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 model, view, projection;
uniform mat3 norm;

void main() {
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
    worldPos = (model * vec4(aPosition, 1.0)).xyz;
    normal = normalize(norm * aNormal);
    texCoord = vec2(aTexCoord.x, -aTexCoord.y);
}
