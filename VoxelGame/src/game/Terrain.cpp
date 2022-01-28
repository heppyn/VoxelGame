#include "Terrain.h"

#include "engine/Chunk.h"
#include "engine/Random.h"


glm::vec2 Terrain::GetTextPos(BlockType blockType) {
    switch (blockType) {
        case BlockType::CactusInside:
            return { 0.0f, 0.0f };
        case BlockType::CactusSide:
            return { 1.0f, 0.0f };
        case BlockType::CactusTop:
            return { 2.0f, 0.0f };
        case BlockType::CottonBlue:
            return { 3.0f, 0.0f };
        case BlockType::CottonBrown:
            return { 4.0f, 0.0f };
        case BlockType::CottonGreen:
            return { 5.0f, 0.0f };
        case BlockType::CottonRed:
            return { 6.0f, 0.0f };
        case BlockType::CottonTan:
            return { 7.0f, 0.0f };
        case BlockType::Dirt:
            return { 0.0f, 1.0f };
        case BlockType::DirtGrass:
            return { 1.0f, 1.0f };
        case BlockType::DirtSand:
            return { 2.0f, 1.0f };
        case BlockType::DirtSnow:
            return { 3.0f, 1.0f };
        case BlockType::Grass1:
            return { 4.0f, 1.0f };
        case BlockType::Grass2:
            return { 5.0f, 1.0f };
        case BlockType::Grass3:
            return { 6.0f, 1.0f };
        case BlockType::Grass4:
            return { 7.0f, 1.0f };
        case BlockType::GrassBrown:
            return { 0.0f, 2.0f };
        case BlockType::GrassTan:
            return { 1.0f, 2.0f };
        case BlockType::GrassTop:
            return { 2.0f, 2.0f };
        case BlockType::GrassTopJungle:
            return { 3.0f, 2.0f };
        case BlockType::GrassTopTundra:
            return { 4.0f, 2.0f };
        case BlockType::GravelDirt:
            return { 5.0f, 2.0f };
        case BlockType::GravelStone:
            return { 6.0f, 2.0f };
        case BlockType::Greysand:
            return { 7.0f, 2.0f };
        case BlockType::Greystone:
            return { 0.0f, 3.0f };
        case BlockType::GreystoneSand:
            return { 1.0f, 3.0f };
        case BlockType::Ice:
            return { 2.0f, 3.0f };
        case BlockType::Lava:
            return { 3.0f, 3.0f };
        case BlockType::Leaves:
            return { 4.0f, 3.0f };
        case BlockType::Leaves2:
            return { 5.0f, 3.0f };
        case BlockType::LeavesOrange:
            return { 6.0f, 3.0f };
        case BlockType::LeavesOrangeTransparent:
            return { 7.0f, 3.0f };
        case BlockType::LeavesTransparent:
            return { 0.0f, 4.0f };
        case BlockType::Redsand:
            return { 1.0f, 4.0f };
        case BlockType::Redstone:
            return { 2.0f, 4.0f };
        case BlockType::RedstoneSand:
            return { 3.0f, 4.0f };
        case BlockType::Rock:
            return { 4.0f, 4.0f };
        case BlockType::RockMoss:
            return { 5.0f, 4.0f };
        case BlockType::Sand:
            return { 6.0f, 4.0f };
        case BlockType::Snow:
            return { 7.0f, 4.0f };
        case BlockType::Stone:
            return { 0.0f, 5.0f };
        case BlockType::StoneDirt:
            return { 1.0f, 5.0f };
        case BlockType::StoneGrass:
            return { 2.0f, 5.0f };
        case BlockType::StoneSand:
            return { 3.0f, 5.0f };
        case BlockType::StoneSnow:
            return { 4.0f, 5.0f };
        case BlockType::TrunkOrangeSide:
            return { 5.0f, 5.0f };
        case BlockType::TrunkSide:
            return { 6.0f, 5.0f };
        case BlockType::TrunkTop:
            return { 7.0f, 5.0f };
        case BlockType::TrunkWhiteSide:
            return { 0.0f, 6.0f };
        case BlockType::TrunkWhiteTop:
            return { 1.0f, 6.0f };
        case BlockType::Water:
            return { 2.0f, 6.0f };
    }

    assert(false && "Block with undefined texture");
    return { 0.0f, 0.0f };
}

float Terrain::GetBlockHeight(const glm::vec2& pos) {
    constexpr auto freq = 100.0f;
    constexpr auto baseHeight = 40.0f;

    // TODO: Redo terrain variation
    constexpr auto heightVar = 10.0f;
    constexpr auto freq2 = 2.5f;
    const glm::vec2 perPos = {
        pos.x / Chunk::ChunkSize / freq2,
        pos.y / Chunk::ChunkSize / freq2
    };

    const auto height = std::floor(
      baseHeight * Engine::Random::Perlin.noise2D_0_1(pos.x / freq, pos.y / freq)
      + heightVar * Engine::Random::Perlin.normalizedOctaveNoise2D_0_1(perPos.x, perPos.y, 2));

    // don't create any block below global water level
    return height >= Detail::WATER_LEVEL ? height : Detail::WATER_LEVEL;
}
