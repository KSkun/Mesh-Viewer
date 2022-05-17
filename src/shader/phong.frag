#version 330 core

in vec3 worldPos;
in vec3 normal;
in vec2 texCoord;

out vec4 FragColor;

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

const float gamma = 2.2;

uniform vec3 eyePos;
uniform Material material;
uniform Light light;

void main() {
    vec3 view = normalize(eyePos - worldPos);
    vec3 lightDir = normalize(light.position - worldPos);
    vec3 halfway = normalize(view + lightDir);
    float lightDist = length(light.position - worldPos);
    float dotNL = max(dot(normal, lightDir), 0.0);
    float dotNH = max(dot(normal, halfway), 0.0);

    vec3 diffuseColor = pow(texture(material.diffuse, texCoord).rgb, vec3(gamma));
    vec3 specularColor = pow(texture(material.specular, texCoord).rgb, vec3(gamma));

    // attenuation value to cover a distance of 32
    // see https://learnopengl.com/Lighting/Light-casters
    float atten = 1.0 / (1.0 + 0.14 * lightDist + 0.07 * lightDist * lightDist);
    vec3 Lambient = light.ambient * diffuseColor;
    vec3 Ldiffuse = light.diffuse * diffuseColor * dotNL * atten;
    vec3 Lspecular = light.specular * specularColor * pow(dotNH, material.shininess) * atten;
    vec3 Lo = Lambient + Ldiffuse + Lspecular;

    vec3 LoMapped = Lo / (Lo + vec3(1.0));
    FragColor.rgb = pow(LoMapped, vec3(1.0 / gamma));
    FragColor.a = 1.0;
}