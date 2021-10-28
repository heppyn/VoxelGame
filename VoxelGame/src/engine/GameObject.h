#pragma once
#include <map>
#include <memory>
#include <typeinfo>

#include "glm/vec3.hpp"
#include "renderer/CubeRenderer.h"
#include "renderer/Texture2D.h"
#include "Components/Component.h"

class GameObject {
  private:
    std::vector<std::unique_ptr<Components::Component>> Components_{};
    std::map<const std::type_info*, Components::Component*> ComponentTypeMap_{};

  public:
    GameObject() = default;
    //TODO: add factories for game objects
    GameObject(glm::vec3 position, glm::vec2 texPos);
    GameObject(glm::vec3 position, Renderer::Texture2D* texture, bool batched = false);
    GameObject(glm::vec3 position, const std::vector<Renderer::Texture2D*>& textures, bool batched = false);
    GameObject(const GameObject& other) = delete; // not supported yet
    GameObject& operator=(const GameObject& other) = delete;
    GameObject(GameObject&& other) noexcept;
    GameObject& operator=(GameObject&& other) noexcept;
    virtual ~GameObject() = default;

    template<typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args) {
        //TODO: https://codereview.stackexchange.com/questions/84176/proper-use-of-type-info-in-relation-to-mapping-components-to-a-type
        Components_.push_back(
          std::make_unique<T>(std::forward<TArgs>(args)...));
        auto* newComp = Components_.back().get();

        newComp->Owner = this;
        ComponentTypeMap_[&typeid(T)] = newComp;
        newComp->Initialize();

        return *static_cast<T*>(newComp);
    }

    template<typename T>
    [[nodiscard]] const T& GetComponent() const {
        return *static_cast<T*>(ComponentTypeMap_.at(&typeid(T)));
    }

    template<typename T>
    [[nodiscard]] T& GetComponent() {
        return *static_cast<T*>(ComponentTypeMap_.at(&typeid(T)));
    }

    template<typename T>
    [[nodiscard]] bool HasComponent() const noexcept {
        return ComponentTypeMap_.count(&typeid(T));
    }

    virtual void Draw(const Renderer::CubeRenderer& renderer) const;
    [[nodiscard]] const glm::vec3& Position() const;
    [[nodiscard]] const glm::vec3& Scale() const;
    void Scale(const glm::vec3& scale);
    void Move(const glm::vec3& dv);
};
