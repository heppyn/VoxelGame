#include "GameObjectFactory.h"
GameObjectFactory::GameObjectFactory(const glm::vec3& scale, const glm::vec3& positionOffset)
  : Scale_(scale)
  , PositionOffset_(positionOffset)
  , OrigPosOffset_(positionOffset) {}

GameObject GameObjectFactory::CreateObject(const glm::vec3& pos, const glm::vec2& tex) {
    return GameObject(pos, tex);
}

GameObject GameObjectFactory::CreateObject(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& scale) {
    auto go = CreateObject(pos, tex);
    go.Scale(scale);

    return go;
}

GameObject GameObjectFactory::CreateObject(const glm::vec3& pos, const glm::vec2& tex, float scale) {
    return CreateObject(pos, tex, glm::vec3(scale));
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

GameObject GameObjectFactory::CreateObjectNoTex(const glm::vec3& pos) {
    return GameObject(pos);
}
GameObject GameObjectFactory::CreateObjectNoTex(const glm::vec3& pos, const glm::vec3& scale) {
    auto go = CreateObjectNoTex(pos);
    go.Scale(scale);

    return go;
}
GameObject GameObjectFactory::CreateObjectNoTex(const glm::vec3& pos, float scale) {
    return CreateObjectNoTex(pos, glm::vec3(scale));
}

GameObjectFactory& GameObjectFactory::Scale(const glm::vec3& scale) {
    Scale_ = scale;
    return *this;
}
GameObjectFactory& GameObjectFactory::PositionOffset(const glm::vec3& positionOffset) {
    PositionOffset_ = positionOffset;
    return *this;
}
