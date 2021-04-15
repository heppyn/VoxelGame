#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    float shininess;
};

uniform Material material;

struct Light {
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
// you don't need this if you move to view space
uniform vec3 view_pos;

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoord));

    // diffuse
    vec3 norm = normalize(Normal);
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

    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    // lesser ambient so multiple lights dont add up
    // TODO: add directional light
    vec3 resultColor = ambient + attenuation * (diffuse + specular);

    FragColor = vec4(resultColor, 1.0);
}