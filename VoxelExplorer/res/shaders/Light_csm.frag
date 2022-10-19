#version 460 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
}
fs_in;

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
uniform sampler2DArray texture_shadow;

uniform vec3 viewPos;

uniform mat4 view;

#define CASCADE_COUNT 3

layout(std140, binding = 0) uniform LightSpaceMatrices {
    mat4 lightSpaceMatrices[CASCADE_COUNT];
};
uniform float cascadePlaneDistances[CASCADE_COUNT - 1];
uniform float cascadeBiases[CASCADE_COUNT];


float ShadowCalculation(vec3 fragPosWorldSpace, float dotLightNormal) {
    // select cascade layer
    vec4 fragPosViewSpace = view * vec4(fragPosWorldSpace, 1.0);
    float depthValue = abs(fragPosViewSpace.z);

    int layer = CASCADE_COUNT - 1;
    for (int i = 0; i < CASCADE_COUNT - 1; ++i) {
        if (depthValue < cascadePlaneDistances[i]) {
            layer = i;
            break;
        }
    }

    vec4 fragPosLightSpace = lightSpaceMatrices[layer] * vec4(fragPosWorldSpace, 1.0);
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    // fragment is outside of the shadow map
    if (currentDepth > 1.0) {
        return 0.0;
    }

    // calculate bias (based on depth map resolution and slope)
    float bias = max(0.0085 * (1.0 - dotLightNormal), 0.00085);
    bias *= cascadeBiases[layer];

//    float closestDepth = texture(texture_shadow, vec3(projCoords.xy, layer)).r;
//    float shadow = (currentDepth - bias) > closestDepth  ? 1.0 : 0.0;

    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(texture_shadow, 0));
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(texture_shadow, vec3(projCoords.xy + vec2(x, y) * texelSize, layer)).r;
            shadow += (currentDepth - bias) > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}

void main() {
    float alpha = vec4(texture(texture_diffuse1, fs_in.TexCoords)).a;
    // don't process fragments which are transparent - threshold is arbitrary number
    if (alpha < 0.05)
        discard;

    vec3 norm = normalize(fs_in.Normal);

    // global
    float dotLightNormal = dot(norm, normalize(-light.globalDir));
    float globalInt = max(dotLightNormal, 0.0);
    vec3 global = globalInt * light.global * vec3(texture(texture_diffuse1, fs_in.TexCoords));

    // ambient
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, fs_in.TexCoords));

    // diffuse
    vec3 lightDir = normalize(light.position - fs_in.FragPos);
    // angle > 90 is negative - don't be nagative
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * vec3(texture(texture_diffuse1, fs_in.TexCoords));

    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    // direction from light to fragment -> -lightDir
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * light.specular * vec3(texture(texture_specular1, fs_in.TexCoords));

    float distance = length(light.position - fs_in.FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // lesser ambient so multiple lights dont add up
    // TODO: add directional light
    // TODO: add point shadows
    float shadow = ShadowCalculation(fs_in.FragPos, dotLightNormal);
    vec3 resultColor = (1.0 - shadow) * global + ambient + attenuation * (diffuse + specular);

    FragColor = vec4(resultColor, alpha);
}
