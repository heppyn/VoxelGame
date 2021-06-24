#include "Terrain.h"


glm::vec2 Terrain::GetTextPos(BlockType blockType) {
    switch (blockType) {
        case BlockType::Water:
            return { 7.0f, 9.0f };
        case BlockType::Stone:
            return { 3.0f, 4.0f };
        case BlockType::Sand:
            return { 7.0f, 6.0f };
        case BlockType::Dirt:
            return { 7.0f, 5.0f };
        case BlockType::Grass:
            return { 8.0f, 0.0f };
        case BlockType::OakLog:
            return { 1.0f, 0.0f };
        case BlockType::OakLeaf:
            return { 5.0f, 1.0f };
    }

    assert("Block with undefined texture", false);
    return { 0.0f, 0.0f };
}
