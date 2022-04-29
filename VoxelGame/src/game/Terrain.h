#pragma once
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

namespace Terrain {
/**
 * \brief Contains all available block types
 */
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
bool IsWater(float height);
bool IsWater(const glm::vec2& pos);
bool IsNextToWater(const glm::vec3& pos, float range);

namespace Detail {
    float WorldHeight(const glm::vec2& pos);
    float Valley(const glm::vec2& pos);
    float Hilliness(const glm::vec2& pos);
} // namespace Detail
} // namespace Terrain
