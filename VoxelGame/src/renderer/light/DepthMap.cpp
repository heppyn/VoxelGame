#include "DepthMap.h"

#include <glad/glad.h>

Renderer::DepthMap::DepthMap(int width, int height)
  : Width(width), Height(height) {}

void Renderer::DepthMap::Init() {
    // generate texture
    Texture_.Type = "texture_shadow";
    Texture_.InternalFormat = GL_DEPTH_COMPONENT;
    Texture_.ImageFormat = GL_DEPTH_COMPONENT;
    Texture_.DataType = GL_FLOAT;
    Texture_.WrapS = GL_CLAMP_TO_BORDER;
    Texture_.WrapT = GL_CLAMP_TO_BORDER;
    Texture_.FilterMin = GL_NEAREST;
    Texture_.FilterMax = GL_NEAREST;

    Texture_.Generate(Width, Height, nullptr);

    glBindTexture(GL_TEXTURE_2D, Texture_.Id);
    // set no shadow outside of the shadow map
    constexpr float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach to framebuffer
    glGenFramebuffers(1, &FBO_);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Texture_.Id, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    // bind default buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DepthMap::Bind() const {
    glViewport(0, 0, Width, Height);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    glClear(GL_DEPTH_BUFFER_BIT);
    BindTexture();
}

void Renderer::DepthMap::BindTexture(unsigned slot) const {
    Texture_.Bind(slot);
}
