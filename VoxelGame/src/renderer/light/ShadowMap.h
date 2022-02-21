#pragma once
#include <vector>

#include "glm/fwd.hpp"
#include "renderer/Shader.h"

namespace Renderer {
class ShadowMap {
  public:
    const int Resolution{ 1024 };

    ShadowMap() = default;
    explicit ShadowMap(int resolution);

    void Init(int levels, float nearPlane, float farPlane);
    void Bind() const;
    void BindLightSpaceMatrices(const glm::mat4& view, const glm::vec3& lightDir, float fov) const;
    void BindData(Shader& shader) const;
    void BindTextures(unsigned slot = 0) const;

  private:
    unsigned FBO_{ 0 };
    unsigned DepthMapId_{ 0 };
    unsigned MatricesUBO_{ 0 };
    std::vector<float> CascadeLevels_{};
    std::vector<float> CascadeBiases_{};

    float NearPlane_{ 0.1f }, FarPlane_{ 150.0f };

    void SetCascadeLevels(int levels, float farPlane);
    [[nodiscard]] std::vector<glm::mat4> LightSpaceMatrices(const glm::mat4& view, const glm::vec3& lightDir, float fov) const;
    [[nodiscard]] glm::mat4 LightSpaceMatrix(const glm::mat4& view, const glm::vec3& lightDir, float nearPlane, float farPlane, float fov) const;
};

} // namespace Renderer
