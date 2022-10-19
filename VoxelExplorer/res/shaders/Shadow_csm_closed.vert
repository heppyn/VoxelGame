#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in mat4 aInstanceMatrix;

void main() {
    // unpack coords from matrix
    vec2 texPos = vec2(aInstanceMatrix[0].w, aInstanceMatrix[1].w);
    mat4 model = aInstanceMatrix;
    model[0].w = 0;
    model[1].w = 0;

    gl_Position = model * vec4(aPos, 1.0);
}
