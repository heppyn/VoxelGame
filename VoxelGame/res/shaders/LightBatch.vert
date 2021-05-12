#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in mat4 aInstanceMatrix;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    Normal = aNor;
    // costly calculation - consider doing it on CPU
    // only needed for non uniform scaling
//    Normal = mat3(transpose(inverse(model))) * aNor; 
    FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));
}