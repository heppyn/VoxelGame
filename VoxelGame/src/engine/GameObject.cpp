#include "GameObject.h"

#include "Components/Mesh.h"
#include "Components/Transform.h"

GameObject::GameObject(glm::vec3 position, glm::vec2 texPos, bool batched) {
    auto mesh = Renderer::CubeRenderer::GetCubeMesh(texPos, batched);

    AddComponent<Components::Mesh>(mesh);
    AddComponent<Components::Transform>(position);
}

GameObject::GameObject(glm::vec3 position, Renderer::Texture2D* texture, bool batched /*= false*/) {
    auto mesh = Renderer::CubeRenderer::GetCubeMesh(batched);
    mesh.Textures.push_back(*texture);

    AddComponent<Components::Mesh>(mesh);
    AddComponent<Components::Transform>(position);
}

GameObject::GameObject(glm::vec3 position, const std::vector<Renderer::Texture2D*>& textures, bool batched) {
    auto mesh = Renderer::CubeRenderer::GetCubeMesh(batched);
    for (auto* texture : textures) {
        mesh.Textures.push_back(*texture);
    }

    AddComponent<Components::Mesh>(mesh);
    AddComponent<Components::Transform>(position);
}

//GameObject::GameObject(const GameObject&) {
//    assert(false);
//    // don't copy components
//}
//
//GameObject& GameObject::operator=(const GameObject& other) {
//    assert(false);
//    if (this == &other)
//        return *this;
//    return *this;
//}

GameObject::GameObject(GameObject&& other) noexcept {
    *this = std::move(other);
}

GameObject& GameObject::operator=(GameObject&& other) noexcept {
    Components_ = std::move(other.Components_);
    ComponentTypeMap_ = std::move(other.ComponentTypeMap_);

    return *this;
}

void GameObject::Draw(const Renderer::CubeRenderer& renderer) const {
    if (HasComponent<Components::Mesh>())
        renderer.DrawCube(
          GetComponent<Components::Mesh>().Mesh_,
          Position(),
          Scale());
}

const glm::vec3& GameObject::Position() const {
    assert(HasComponent<Components::Transform>());
    return GetComponent<Components::Transform>().Position;
}

const glm::vec3& GameObject::Scale() const {
    assert(HasComponent<Components::Transform>());
    return GetComponent<Components::Transform>().Scale;
}

void GameObject::Scale(const glm::vec3& scale) {
    assert(HasComponent<Components::Transform>());
    GetComponent<Components::Transform>().Scale = scale;
}
