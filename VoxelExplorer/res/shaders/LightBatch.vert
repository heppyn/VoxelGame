#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in mat4 aInstanceMatrix;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 FragPosLightSpace;

uniform mat4 view;
uniform mat4 projection;
uniform vec2 tex_size;
uniform mat4 lightSpaceMatrix;

void main() {
    // unpack coords from matrix
    vec2 texPos = vec2(aInstanceMatrix[0].w, aInstanceMatrix[1].w);
    mat4 model = aInstanceMatrix;
    model[0].w = 0;
    model[1].w = 0;

    vec2 shift = vec2(
        1.0 / tex_size.x * texPos.x,
        1.0 / tex_size.y * texPos.y
    );
    TexCoord = vec2(aTexCoord.x + shift.x, aTexCoord.y + shift.y);
    Normal = aNor;
    // costly calculation - consider doing it on CPU
    // only needed for non uniform scaling
//    Normal = mat3(transpose(inverse(model))) * aNor; 
    FragPos = vec3(model * vec4(aPos, 1.0));
    // transformation to light space -- shadow map is in light space
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
    gl_Position = projection * view * vec4(FragPos, 1.0);
}