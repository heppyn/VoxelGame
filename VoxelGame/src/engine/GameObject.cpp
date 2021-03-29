#include "GameObject.h"

GameObject::GameObject(glm::vec3 position, Renderer::Texture2D* texture)
  : Position(position), Texture(texture) {
}

void GameObject::Draw(const Renderer::CubeRenderer& renderer) const
{
    renderer.DrawCube(Texture, Position);
}
