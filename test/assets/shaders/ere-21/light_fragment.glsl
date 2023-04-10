#version 410 core

uniform vec3 u_cam_pos;

out vec4 FragColor;

in vec3 Normals;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    // color
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // maps
    sampler2D diffuseMap;
    sampler2D specularMap;
    // sampler2D normalMap;
    sampler2D emissionMap;

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

uniform int uDirLightCount;
uniform int uPointLightCount;
uniform int uSpotLightCount;

vec3 CalcDirLight(DirectionalLight light) {
    // ambient
    vec3 ambient = light.ambient * (uMaterial.ambient + texture(uMaterial.diffuseMap, TexCoords).rgb);

    // diffuse
    vec3 norm = normalize(Normals);
    vec3 lightDir;
    if (light.direction.w == 0) {
        lightDir = normalize(-vec3(light.direction));
    } else {
        lightDir = normalize(vec3(light.direction) - FragPos);
    }
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * (uMaterial.diffuse + texture(uMaterial.diffuseMap, TexCoords).rgb));

    // specular
    vec3 viewDir = normalize(u_cam_pos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = light.specular * (spec * (uMaterial.specular + texture(uMaterial.specularMap, TexCoords).rgb));

    vec3 emission = texture(uMaterial.emissionMap, TexCoords).rgb;

    return specular + ambient + diffuse + emission;
}

vec3 CalcPointLight(PointLight light) {
    // ambient
    vec3 ambient = light.ambient * (uMaterial.ambient + texture(uMaterial.diffuseMap, TexCoords).rgb);

    // diffuse
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * (uMaterial.diffuse + texture(uMaterial.diffuseMap, TexCoords).rgb));

    // specular
    vec3 viewDir = normalize(u_cam_pos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = light.specular * (spec * (uMaterial.specular + texture(uMaterial.specularMap, TexCoords).rgb));

    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 emission = texture(uMaterial.emissionMap, TexCoords).rgb;

    return specular + ambient + diffuse + emission;
}

vec3 CalcSpotLight(SpotLight light) {
    // ambient
    vec3 ambient = light.ambient * (uMaterial.ambient + texture(uMaterial.diffuseMap, TexCoords).rgb);

    // diffuse
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * (uMaterial.diffuse + texture(uMaterial.diffuseMap, TexCoords).rgb));

    // specular
    vec3 viewDir = normalize(u_cam_pos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = light.specular * (spec * (uMaterial.specular + texture(uMaterial.specularMap, TexCoords).rgb));

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

    vec3 emission = texture(uMaterial.emissionMap, TexCoords).rgb;

    return specular + ambient + diffuse + emission;
}

void main() {
    vec3 result = vec3(0.0, 0.0, 0.0f);

    for (int i = 0; i < uDirLightCount; i++) {
        result += CalcDirLight(uDirLights[i]);
    }

    for (int i = 0; i < uPointLightCount; i++) {
        result += CalcPointLight(uPointLights[i]);
    }

    for (int i = 0; i < uSpotLightCount; i++) {
        result += CalcSpotLight(uSpotLights[i]);
    }

    FragColor = vec4(result, 1.0);
}
