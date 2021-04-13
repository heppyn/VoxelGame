#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

float specularStrength = 0.5;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light_pos - FragPos);

    vec3 ambient = 0.1 * light_color;
    // angle > 90 is negative - don't be nagative
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 viewDir = normalize(view_pos - FragPos);
    // direction from light to fragment -> -lightDir
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light_color; 

    vec3 resultColor = ambient + diffuse + specular;

    FragColor = vec4(resultColor, 1.0) * texture(texture_diffuse1, TexCoord);
}