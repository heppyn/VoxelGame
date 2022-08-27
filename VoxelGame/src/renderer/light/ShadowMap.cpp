#include "ShadowMap.h"

#include <glad/glad.h>

#include "glm/ext/matrix_clip_space.hpp"
#include "open_gl/WindowManagerGl.h"
#include "helpers/Math.h"
#include "engine/Log.h"


Renderer::ShadowMap::ShadowMap(int resolution)
  : Resolution(resolution) {}

Renderer::ShadowMap::~ShadowMap() {
    glDeleteFramebuffers(1, &FBO_);
    glDeleteTextures(1, &DepthMapId_);
    glDeleteBuffers(1, &MatricesUBO_);
}

void Renderer::ShadowMap::Init(const int levels, float nearPlane, const float farPlane) {
    NearPlane_ = nearPlane;
    FarPlane_ = farPlane;
    SetCascadeLevels(levels, farPlane);

    glGenFramebuffers(1, &FBO_);

    glGenTextures(1, &DepthMapId_);
    glBindTexture(GL_TEXTURE_2D_ARRAY, DepthMapId_);
    glTexImage3D(
      GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT32F, Resolution, Resolution, CascadeLevels_.size() + 1, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    constexpr float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthMapId_, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG_ENGINE_ERROR("FRAMEBUFFER: Framebuffer is not complete!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // configure buffer for matrices
    glGenBuffers(1, &MatricesUBO_);
    glBindBuffer(GL_UNIFORM_BUFFER, MatricesUBO_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4) * levels, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, MatricesUBO_);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Renderer::ShadowMap::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    glBindTexture(GL_TEXTURE_2D_ARRAY, DepthMapId_);
    glViewport(0, 0, Resolution, Resolution);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::ShadowMap::BindLightSpaceMatrices(const glm::mat4& view, const glm::vec3& lightDir, float fov) const {
    const auto lightMatrices = LightSpaceMatrices(view, lightDir, fov);
    glBindBuffer(GL_UNIFORM_BUFFER, MatricesUBO_);
    for (size_t i = 0; i < lightMatrices.size(); ++i) {
        glBufferSubData(GL_UNIFORM_BUFFER, i * sizeof(glm::mat4x4), sizeof(glm::mat4x4), &lightMatrices[i]);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Renderer::ShadowMap::BindData(Shader& shader) const {
    shader.SetInteger("texture_shadow", 3);
    BindTextures(3);

    for (size_t i = 0; i < CascadeLevels_.size(); ++i) {
        shader.SetFloat(std::string("cascadePlaneDistances[" + std::to_string(i) + "]").c_str(), CascadeLevels_[i]);
    }
    for (size_t i = 0; i < CascadeBiases_.size(); ++i) {
        shader.SetFloat(std::string("cascadeBiases[" + std::to_string(i) + "]").c_str(), CascadeBiases_[i]);
    }
}

void Renderer::ShadowMap::BindTextures(unsigned slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D_ARRAY, DepthMapId_);
}

void Renderer::ShadowMap::SetCascadeLevels(int levels, float farPlane) {
    assert(levels > 1);

    if (levels == 3) {
        CascadeLevels_ = { farPlane / 16.0f, farPlane / 4.0f };
        CascadeBiases_ = { 0.1f, 0.03f, 0.009f };
    }
    else if (levels == 4) {
        CascadeLevels_ = { farPlane / 25.0f, farPlane / 10.0f, farPlane / 3.5f };
        CascadeBiases_ = { 0.2f, 0.1f, 0.05f, 0.01f };
    }
    else if (levels == 5) {
        CascadeLevels_ = { farPlane / 30.0f, farPlane / 16.0f, farPlane / 8.0f, farPlane / 3.5f };
        CascadeBiases_ = { 0.2f, 0.1f, 0.09f, 0.07f, 0.01f };
    }
    else {
        assert(false && "Unsuported cascade number");
    }

    assert(CascadeLevels_.size() + 1 == CascadeBiases_.size());

    size_t i = 0;
    for (; i < CascadeLevels_.size(); ++i) {
        CascadeBiases_[i] = 1 / (CascadeBiases_[i] * CascadeLevels_[i]);
    }
    CascadeBiases_[i] = 1 / (CascadeBiases_[i] * farPlane);
}

std::vector<glm::mat4> Renderer::ShadowMap::LightSpaceMatrices(const glm::mat4& view, const glm::vec3& lightDir, float fov) const {
    std::vector<glm::mat4> res;

    for (size_t i = 0; i < CascadeLevels_.size() + 1; ++i) {
        if (i == 0) {
            res.push_back(LightSpaceMatrix(view, lightDir, NearPlane_, CascadeLevels_[i], fov));
        }
        else if (i < CascadeLevels_.size()) {
            res.push_back(LightSpaceMatrix(view, lightDir, CascadeLevels_[i - 1], CascadeLevels_[i], fov));
        }
        else {
            res.push_back(LightSpaceMatrix(view, lightDir, CascadeLevels_[i - 1], FarPlane_, fov));
        }
    }

    return res;
}

glm::mat4 Renderer::ShadowMap::LightSpaceMatrix(const glm::mat4& view, const glm::vec3& lightDir, float nearPlane, float farPlane, float fov) const {
    const auto proj = glm::perspective(
      glm::radians(fov),
      static_cast<float>(WindowManagerGl::Width) / static_cast<float>(WindowManagerGl::Height),
      nearPlane,
      farPlane);

    // TODO: scale frustum depending on surrounding height
    return Helpers::Math::OrthoLightSpace(
      Helpers::Math::FrustumCornersWordSpace(proj, view),
      lightDir,
      2.5f);
}
