#version 460 core

layout(triangles, invocations = 3) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 TexCoord;
} gs_in[];

out vec2 TexCoord; 

// max 5 shadow levels
layout(std140, binding = 0) uniform LightSpaceMatrices {
    mat4 lightSpaceMatrices[3];
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
