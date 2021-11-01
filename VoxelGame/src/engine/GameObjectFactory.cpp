#include "GameObjectFactory.h"
GameObjectFactory::GameObjectFactory(const glm::vec3& scale, const glm::vec3& positionOffset)
  : Scale_(scale), PositionOffset_(positionOffset), OrigPosOffset_(positionOffset) {}

GameObject GameObjectFactory::CreateObject(const glm::vec3& pos, const glm::vec2& tex) {
    return GameObject(pos, tex);
}
GameObject GameObjectFactory::CreateFromPreset(const glm::vec3& pos, const glm::vec2& tex) const {
    auto go = CreateObject(pos, tex);
    go.Scale(Scale_);
    go.Move(PositionOffset_);

    return go;
}
GameObject GameObjectFactory::CreateFromPreset(const glm::vec3& pos, const glm::vec2& tex) {
    auto go = CreateObject(pos, tex);
    go.Scale(Scale_);
    go.Move(PositionOffset_);

    return go;
}
GameObject GameObjectFactory::CreateStacked(const glm::vec3& pos, const glm::vec2& tex) {
    auto go = CreateFromPreset(pos, tex);
    // prepare bottom for the next object
    PositionOffset_ += OrigPosOffset_ * 2.0f;

    return go;
}
GameObjectFactory& GameObjectFactory::Scale(const glm::vec3& scale) {
    Scale_ = scale;
    return *this;
}
GameObjectFactory& GameObjectFactory::PositionOffset(const glm::vec3& positionOffset) {
    PositionOffset_ = positionOffset;
    return *this;
}
