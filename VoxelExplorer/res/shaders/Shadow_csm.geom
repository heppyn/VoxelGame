#version 460 core

#define CASCADE_COUNT 3

layout(triangles, invocations = CASCADE_COUNT) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 TexCoord;
} gs_in[];

out vec2 TexCoord; 

layout(std140, binding = 0) uniform LightSpaceMatrices {
    mat4 lightSpaceMatrices[CASCADE_COUNT];
};

void main() {
    for (int i = 0; i < 3; ++i) {
        gl_Position = lightSpaceMatrices[gl_InvocationID] * gl_in[i].gl_Position;
        gl_Layer = gl_InvocationID;
        TexCoord = gs_in[i].TexCoord;
        EmitVertex();
    }
    EndPrimitive();
}
