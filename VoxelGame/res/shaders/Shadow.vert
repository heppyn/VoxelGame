#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in mat4 aInstanceMatrix;

out vec2 TexCoord;

uniform mat4 lightSpaceMatrix;
uniform vec2 tex_size;

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

    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}
