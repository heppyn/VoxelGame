#include "DepthMap.h"

#include <glad/glad.h>

#include "helpers/Math.h"
#include "open_gl/WindowManagerGl.h"

Renderer::DepthMap::DepthMap(int resolution)
  : Resolution(resolution) {}

Renderer::DepthMap::DepthMap(float farPlane, float nearPlane)
  : FarPlane_(farPlane), NearPlane_(nearPlane) {}


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

    Texture_.Generate(Resolution, Resolution, nullptr);

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
    glViewport(0, 0, Resolution, Resolution);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    glClear(GL_DEPTH_BUFFER_BIT);
    BindTexture();
}

void Renderer::DepthMap::BindTexture(unsigned slot) const {
    Texture_.Bind(slot);
}

void Renderer::DepthMap::BindData(Shader& shader) const {
    shader.SetInteger("texture_shadow", 3);
    BindTexture(3);
}

glm::mat4 Renderer::DepthMap::LightSpaceMatrix(const glm::mat4& view, const glm::vec3& lightDir, float fov) const {
    const glm::mat4 projection = glm::perspective(
      glm::radians(fov),
      static_cast<float>(WindowManagerGl::Width) / static_cast<float>(WindowManagerGl::Height),
      NearPlane_,
      FarPlane_);

    return Helpers::Math::OrthoLightSpace(
      Helpers::Math::FrustumCornersWordSpace(projection, view),
      lightDir,
      2.0f);
}
