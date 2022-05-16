#version 330 core

in vec3 worldPos;
in vec3 normal;
in vec2 texCoord;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 eyePos;
uniform Material material;
uniform Light light;

void main() {
    vec3 view = normalize(worldPos - eyePos);
    vec3 lightDir = normalize(worldPos - light.position);
    vec3 halfway = normalize(view + lightDir);
    float lightDist = length(worldPos - light.position);
    float dotNL = max(dot(normal, lightDir), 0.0);
    float dotNH = max(dot(normal, view), 0.0);

    vec3 diffuseColor = texture(material.diffuse, texCoord);
    vec3 specularColor = texture(material.specular, texCoord);

    // attenuation value to cover a distance of 32
    // see https://learnopengl.com/Lighting/Light-casters
    float atten = 1.0 / (1.0 + 0.14 * lightDist + 0.07 * lightDist * lightDist);
    vec3 Lambient = light.ambient * diffuseColor * atten;
    vec3 Ldiffuse = light.diffuse * diffuseColor * dotNL * atten;
    vec3 Lspecular = light.specular * specularColor * pow(dotNH, material.shininess) * atten;
    vec3 Lo = Lambient + Ldiffuse + Lspecular;

    gl_FragColor = vec4(Lo, 1.0);
}