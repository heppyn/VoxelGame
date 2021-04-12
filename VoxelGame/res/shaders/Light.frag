#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
uniform vec3 light_color;

void main()
{
    FragColor = vec4(light_color, 1.0) * texture(texture_diffuse1, TexCoord);
}