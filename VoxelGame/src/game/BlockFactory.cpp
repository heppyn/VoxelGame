#include "BlockFactory.h"

GameObject Terrain::BlockFactory::CreateBlock(const glm::vec3& pos, BlockType blockType) {
    return GameObject(pos, GetTextPos(blockType), true);
}
