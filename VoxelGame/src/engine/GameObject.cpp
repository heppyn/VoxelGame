#include "GameObject.h"

GameObject::GameObject(glm::vec3 position, Renderer::Texture2D* texture, bool batched /*= false*/)
  : Position(position),
    Mesh(Renderer::CubeRenderer::GetCubeMesh(batched)) {
    Mesh.Textures.push_back(*texture);
}

void GameObject::Draw(const Renderer::CubeRenderer& renderer) const {
    renderer.DrawCube(Mesh, Position);
    //renderer.DrawCube(Texture, Position);
}
