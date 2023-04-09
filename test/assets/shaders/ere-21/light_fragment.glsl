#version 410 core

uniform vec3 u_cam_pos;

out vec4 FragColor;

in vec3 Normals;
in vec3 FragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirectionalLight {
    vec4 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
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

#define NR_DIR_LIGHTS 32
#define NR_POINT_LIGHTS 32
#define NR_SPOT_LIGHTS 32

uniform Material uMaterial;
uniform DirectionalLight uDirLights[NR_DIR_LIGHTS];
uniform PointLight uPointLights[NR_POINT_LIGHTS];
uniform SpotLight uSpotLights[NR_SPOT_LIGHTS];

vec3 CalcDirLight(DirectionalLight light) {
    // ambient
    vec3 ambient = light.ambient * uMaterial.ambient;

    // diffuse
    vec3 norm = normalize(Normals);
    vec3 lightDir;
    if (light.direction.w == 0) {
        lightDir = normalize(-vec3(light.direction));
    } else {
        lightDir = normalize(vec3(light.direction) - FragPos);
    }
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * uMaterial.diffuse);

    // specular
    vec3 viewDir = normalize(u_cam_pos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = light.specular * (spec * uMaterial.specular);

    return specular + ambient + diffuse;
}

vec3 CalcPointLight(PointLight light) {
    // ambient
    vec3 ambient = light.ambient * uMaterial.ambient;

    // diffuse
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * uMaterial.diffuse);

    // specular
    vec3 viewDir = normalize(u_cam_pos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = light.specular * (spec * uMaterial.specular);

    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return specular + ambient + diffuse;
}

vec3 CalcSpotLight(SpotLight light) {
    // ambient
    vec3 ambient = light.ambient * uMaterial.ambient;

    // diffuse
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * uMaterial.diffuse);

    // specular
    vec3 viewDir = normalize(u_cam_pos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = light.specular * (spec * uMaterial.specular);

    // spotlight
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return specular + ambient + diffuse;
}

void main() {
    SpotLight light = uSpotLights[0];

    vec3 result = CalcSpotLight(light);

    FragColor = vec4(result, 1.0);
}
