#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 Color;

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

void main() {
	FragColor = Color;
}