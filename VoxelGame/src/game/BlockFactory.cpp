#include "BlockFactory.h"


Terrain::BlockFactory::BlockFactory(const glm::vec3& scale, const glm::vec3& positionOffset)
  : Scale_(scale), PositionOffset_(positionOffset) {}

GameObject Terrain::BlockFactory::CreateBlock(const glm::vec3& pos, BlockType blockType) {
    return GameObject(pos, GetTextPos(blockType), true);
}

GameObject Terrain::BlockFactory::CreateFromPreset(const glm::vec3& pos, BlockType blockType) const {
    auto go = CreateBlock(pos, blockType);
    go.Scale(Scale_);
    go.Move(PositionOffset_);

    return go;
}

Terrain::BlockFactory& Terrain::BlockFactory::Scale(const glm::vec3& scale) {
    Scale_ = scale;
    return *this;
}

Terrain::BlockFactory& Terrain::BlockFactory::PositionOffset(const glm::vec3& positionOffset) {
    PositionOffset_ = positionOffset;
    return *this;
}
