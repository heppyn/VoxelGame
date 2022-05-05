#version 330 core

in vec2 TexCoord;

uniform sampler2D texture_diffuse1;

void main() {
    float alpha = vec4(texture(texture_diffuse1, TexCoord)).a;
    // don't process fragments which are transparent - threshold is arbitrary number 
    if (alpha < 0.05)
        discard;

    gl_FragDepth = gl_FragCoord.z;
}
