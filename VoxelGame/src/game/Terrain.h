#pragma once
#include <vector>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

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
bool IsWater(float height);
bool IsWater(const glm::vec2& pos);
bool IsNextToWater(const glm::vec3& pos, float range);

namespace Detail {
    constexpr float WATER_LEVEL{ 15.0f };
    constexpr float MOUNTAINS_F{ 200.0f };
    constexpr float VALLEY_F{ 20.0f };
    constexpr float HILLINESS_F{ 300.0f };

    inline std::vector<std::pair<float, float>> mountainSplices = { { 0.0f, 0.0f }, { 0.1f, 1.0f }, { 0.5, 20.f }, { 0.6f, 60.0f }, { 1.0f, 70.0f }, { 1.1f, 70.0f } };

    float WorldHeight(const glm::vec2& pos);
    float Valley(const glm::vec2& pos);
    float Hilliness(const glm::vec2& pos);
} // namespace Detail
} // namespace Terrain
