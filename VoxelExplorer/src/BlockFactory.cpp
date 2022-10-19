#include "BlockFactory.h"


Terrain::BlockFactory::BlockFactory(const glm::vec3& scale, const glm::vec3& positionOffset)
  : GOFactory_(scale, positionOffset) {}

GameObject Terrain::BlockFactory::CreateBlock(const glm::vec3& pos, BlockType blockType) {
    return GameObjectFactory::CreateObject(pos, GetTextPos(blockType));
}

GameObject Terrain::BlockFactory::CreateFromPreset(const glm::vec3& pos, BlockType blockType) const {
    return GOFactory_.CreateFromPreset(pos, GetTextPos(blockType));
}

GameObject Terrain::BlockFactory::CreateFromPreset(const glm::vec3& pos, BlockType blockType) {
    return GOFactory_.CreateFromPreset(pos, GetTextPos(blockType));
}

GameObject Terrain::BlockFactory::CreateStacked(const glm::vec3& pos, BlockType blockType) {
    return GOFactory_.CreateStacked(pos, GetTextPos(blockType));
}

Terrain::BlockFactory& Terrain::BlockFactory::Scale(const glm::vec3& scale) {
    GOFactory_.Scale(scale);
    return *this;
}

Terrain::BlockFactory& Terrain::BlockFactory::PositionOffset(const glm::vec3& positionOffset) {
    GOFactory_.PositionOffset(positionOffset);
    return *this;
}
