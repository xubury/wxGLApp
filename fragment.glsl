#version 330 core
out vec4 fragColor;

uniform sampler2D uDepthMap;

struct Material {
    sampler2D ambient0;

    sampler2D diffuse0;
    sampler2D diffuse1;
    sampler2D diffuse2;

    sampler2D specular0;
    sampler2D specular1;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;
in vec3 viewPos;
in vec4 fragPosLightSpace;

uniform PointLight uPointLight;
uniform DirLight uDirLight;

uniform Material uMaterial;


void main() {
    fragColor = vec4(texture(uMaterial.diffuse0, texCoord).rgb, 1.0);
}
