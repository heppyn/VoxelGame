#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in mat4 aInstanceMatrix;
// does this really work?
layout(location = 6) in vec4 aTexPos;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 view;
uniform mat4 projection;
uniform vec2 tex_size;

void main() {
    gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0);
    vec2 shift = vec2(
        1.0 / tex_size.x * aTexPos.x,
        1.0 / tex_size.y * aTexPos.y
    );
    TexCoord = vec2(aTexCoord.x + shift.x, aTexCoord.y + shift.y);
    Normal = aNor;
    // costly calculation - consider doing it on CPU
    // only needed for non uniform scaling
//    Normal = mat3(transpose(inverse(model))) * aNor; 
    FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));
}