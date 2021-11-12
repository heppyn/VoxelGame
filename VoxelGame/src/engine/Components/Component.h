#pragma once
//#include "engine/GameObject.h"

class GameObject;

namespace Components {
class Component {
  public:
    GameObject* Owner{ nullptr };

    Component() = default;
    Component(const Component&) = default;
    Component& operator=(const Component&) = default;
    Component(Component&&) = default;
    Component& operator=(Component&&) = default;

    virtual ~Component() = default;
    virtual void Initialize() {}
    virtual void Update([[maybe_unused]] const float delta) {}
    virtual void Render() const {}
};
} // namespace Components
