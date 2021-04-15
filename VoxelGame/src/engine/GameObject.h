#pragma once
#include "glm/vec3.hpp"
#include "renderer/CubeRenderer.h"
#include "renderer/Texture2D.h"

class GameObject {
  private:
    glm::vec3 Position{ 0 };
    glm::vec3 Scale_{ 1 };
    // TODO: set default "missing texture"
    Renderer::Mesh Mesh{};
    Renderer::Texture2D* Texture{ nullptr };

  public:
    GameObject() = default;
    GameObject(glm::vec3 position, Renderer::Texture2D* texture, bool batched = false);
    GameObject(glm::vec3 position, const std::vector<Renderer::Texture2D*>& textures, bool batched = false);
    virtual ~GameObject() = default;

    virtual void Draw(const Renderer::CubeRenderer& renderer) const;
    [[nodiscard]] const glm::vec3& GetPosition() const { return Position; }
    [[nodiscard]] Renderer::Texture2D* GetTexture() const { return Texture; }
    [[nodiscard]] const glm::vec3& Scale() const { return Scale_; }
    void Scale(const glm::vec3& scale) { Scale_ = scale; }
};
