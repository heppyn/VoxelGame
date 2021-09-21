#include "Terrain.h"
#include "engine/Random.h"


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
        case BlockType::GrassDark:
            return { 7.0f, 8.0f };
        case BlockType::GrassOrange:
            return { 5.0f, 0.0f };
        case BlockType::OakLog:
            return { 1.0f, 0.0f };
        case BlockType::OakLeaf:
            return { 5.0f, 1.0f };
        case BlockType::Snow:
            return { 3.0f, 5.0f };
        case BlockType::Ice:
            return { 0.0f, 6.0f };
        case BlockType::DirtStones:
            return { 6.0f, 0.0f };
        case BlockType::Cactus:
            return { 4.0f, 8.0f };
    }

    assert("Block with undefined texture", false);
    return { 0.0f, 0.0f };
}

float Terrain::GetBaseHeight(const glm::vec2& pos)
{
    const auto freq = 100.0f;
    const auto height = 40.0f;
    return height * Engine::Random::Perlin.noise2D_0_1(pos.x / freq, pos.y / freq);
}
