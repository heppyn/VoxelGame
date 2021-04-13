#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
uniform vec3 light_color; // used for consitency
uniform vec3 light_pos;   // used for consitency

void main()
{
    FragColor = texture(texture_diffuse1, TexCoord);
}