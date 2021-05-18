#pragma once

#include "Component.h"
#include "renderer/Mesh.h"
#include "renderer/Shader.h"

namespace Components {
class Mesh : public Component {
  public:
    Renderer::Mesh Mesh_;

    Mesh() = delete;
    explicit Mesh(Renderer::Mesh mesh) : Mesh_(std::move(mesh)) {}
    ~Mesh() override = default;
    Mesh(const Mesh&) = default;
    Mesh& operator=(const Mesh&) = default;
    Mesh(Mesh&&) = default;
    Mesh& operator=(Mesh&&) = default;
};
} // namespace Components
