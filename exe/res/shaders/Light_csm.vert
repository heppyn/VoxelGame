#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in mat4 aInstanceMatrix;


out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
}
vs_out;

uniform mat4 view;
uniform mat4 projection;
uniform vec2 tex_size;

void main() {
    // unpack coords from matrix
    vec2 texPos = vec2(aInstanceMatrix[0].w, aInstanceMatrix[1].w);
    mat4 model = aInstanceMatrix;
    model[0].w = 0;
    model[1].w = 0;

    vec2 shift = vec2(
      1.0 / tex_size.x * texPos.x,
      1.0 / tex_size.y * texPos.y);

    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = aNor;
    vs_out.TexCoords = vec2(aTexCoords.x + shift.x, aTexCoords.y + shift.y);
    gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
}
