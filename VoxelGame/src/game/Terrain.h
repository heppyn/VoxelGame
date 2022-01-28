#pragma once
#include "glm/vec2.hpp"

namespace Terrain {
enum class BlockType {
    CactusInside,
    CactusSide,
    CactusTop,
    CottonBlue,
    CottonBrown,
    CottonGreen,
    CottonRed,
    CottonTan,
    Dirt,
    DirtGrass,
    DirtSand,
    DirtSnow,
    Grass1,
    Grass2,
    Grass3,
    Grass4,
    GrassBrown,
    GrassTan,
    GrassTop,
    GrassTopJungle,
    GrassTopTundra,
    GravelDirt,
    GravelStone,
    Greysand,
    Greystone,
    GreystoneSand,
    Ice,
    Lava,
    Leaves,
    Leaves2,
    LeavesOrange,
    LeavesOrangeTransparent,
    LeavesTransparent,
    Redsand,
    Redstone,
    RedstoneSand,
    Rock,
    RockMoss,
    Sand,
    Snow,
    Stone,
    StoneDirt,
    StoneGrass,
    StoneSand,
    StoneSnow,
    TrunkOrangeSide,
    TrunkSide,
    TrunkTop,
    TrunkWhiteSide,
    TrunkWhiteTop,
    Water,
};

glm::vec2 GetTextPos(BlockType blockType);

float GetBlockHeight(const glm::vec2& pos);

namespace Detail {
    constexpr float WATER_LEVEL{ 15.0f };
}
} // namespace Terrain
