#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;

struct Material {
    float shininess;
};

uniform Material material;

struct Light {
    vec3 global;
    vec3 globalDir;

    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light light;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_shadow;

// you don't need this if you move to view space
uniform vec3 view_pos;

float ShadowCalculation(vec4 fragPosLightSpace, float dotLightNormal) {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // NDC [0, 1]
    projCoords = projCoords * 0.5 + 0.5;

    // outside of far plane of the frustum
    // is it good idea to branch in shader?
    if (projCoords.z > 1.0)
        return 0.0;

    float closestDepth = texture(texture_shadow, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float bias = max(0.015 * (1.0 - dotLightNormal), 0.0015);

    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    // sample surrounding texels for smoother shadow edges
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(texture_shadow, 0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(texture_shadow, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}

void main() {
    float alpha = vec4(texture(texture_diffuse1, TexCoord)).a;
    // don't process fragments which are transparent - threshold is arbitrary number
    if (alpha < 0.05)
        discard;

    vec3 norm = normalize(Normal);

    // global
    float dotLightNormal = dot(norm, normalize(-light.globalDir));
    float globalInt = max(dotLightNormal, 0.0);
    vec3 global = globalInt * light.global * vec3(texture(texture_diffuse1, TexCoord));

    // ambient
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoord));

    // diffuse
    vec3 lightDir = normalize(light.position - FragPos);
    // angle > 90 is negative - don't be nagative
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * vec3(texture(texture_diffuse1, TexCoord));

    // specular
    vec3 viewDir = normalize(view_pos - FragPos);
    // direction from light to fragment -> -lightDir
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * light.specular * vec3(texture(texture_specular1, TexCoord));

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // lesser ambient so multiple lights dont add up
    // TODO: add directional light
    // TODO: add point shadows
    float shadow = ShadowCalculation(FragPosLightSpace, dotLightNormal);
    vec3 resultColor = (1.0 - shadow) * global + ambient + attenuation * (diffuse + specular);

    FragColor = vec4(resultColor, alpha);
}
