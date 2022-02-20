#pragma once

#include "renderer/Shader.h"
#include "renderer/Texture2D.h"

namespace Renderer {
// framebuffer with attached dept component
class DepthMap {
  public:
    const int Resolution{ 4096 };

    DepthMap() = default;
    DepthMap(int resolution);
    DepthMap(float farPlane, float nearPlane = 0.1f);
    void Init();
    void Bind() const;
    void BindTexture(unsigned slot = 0) const;
    void BindData(Shader& shader) const;

    [[nodiscard]] glm::mat4 LightSpaceMatrix(const glm::mat4& view, const glm::vec3& lightDir, float fov) const;

  private:
    unsigned FBO_{ 0 };
    Texture2D Texture_{};
    float FarPlane_{ 90.0f };
    float NearPlane_{ 0.1f };
};
} // namespace Renderer
