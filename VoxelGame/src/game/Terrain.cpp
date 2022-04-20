#include "Terrain.h"

#include "engine/Chunk.h"
#include "engine/Random.h"
#include "helpers/Math.h"

namespace Terrain::Detail {
constexpr float WATER_LEVEL{ 18.0f };
// prime number to eliminate periodicity
constexpr float BASE_F{ 149.0f };
constexpr float DETAIL_F{ 53.0f };
constexpr float MOUNTAINS_F{ 199.0f };
constexpr float VALLEY_F{ 31.0f };
constexpr float HILLINESS_F{ 701.0f };

inline std::vector<std::pair<float, float>> mountainSplices = { { 0.0f, 0.0f }, { 0.1f, 1.0f }, { 0.5f, 20.f }, { 0.65f, 60.0f }, { 1.0f, 70.0f }, { 1.1f, 70.0f } };
} // namespace Terrain::Detail


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
    const auto worldHeight = Detail::WorldHeight(pos);
    constexpr auto baseHeight = 50.0f;
    constexpr auto heightVar = 10.0f;

    const auto height = std::floor(
      worldHeight
      + baseHeight * Engine::Random::Perlin.noise2D_0_1(pos.x / Detail::BASE_F, pos.y / Detail::BASE_F)
      + heightVar * Engine::Random::Simplex.fractal0_1(2, pos.x / Detail::DETAIL_F, pos.y / Detail::DETAIL_F));

    // don't create any block below global water level
    return height >= Detail::WATER_LEVEL ? height : Detail::WATER_LEVEL;
}

bool Terrain::IsWater(const float height) {
    return Helpers::Math::Equal(height, Detail::WATER_LEVEL);
}

bool Terrain::IsWater(const glm::vec2& pos) {
    return IsWater(GetBlockHeight(pos));
}

bool Terrain::IsNextToWater(const glm::vec3& pos, const float range) {
    assert(range >= 1.0f);

    // don't place sand next to water
    // sand only until some point in height
    if (pos.y > Detail::WATER_LEVEL + 1.0f && range <= 1.0f || pos.y > Detail::WATER_LEVEL + 3.0f) {
        return false;
    }

    // TODO: is this the most performance efficient?
    const std::vector neigh = {
        glm::vec2(pos.x + range, pos.z),
        glm::vec2(pos.x - range, pos.z),
        glm::vec2(pos.x, pos.z + range),
        glm::vec2(pos.x, pos.z - range)
    };

    // overloaded functions don't work
    return std::ranges::any_of(neigh, [](const glm::vec2& p) { return IsWater(p); });
}

float Terrain::Detail::WorldHeight(const glm::vec2& pos) {
    const auto hilliness = Hilliness(pos);
    if (Helpers::Math::Equal(hilliness, 0.0f))
        return 0.0f;

    const auto val = Engine::Random::Simplex.noise0_1(pos.x / MOUNTAINS_F, pos.y / MOUNTAINS_F);

    size_t i = 0;
    for (; i < mountainSplices.size() - 1; ++i) {
        if (val >= mountainSplices[i].first && val <= mountainSplices[i + 1].first) {
            break;
        }
    }

    const float percent = Helpers::Math::Map(val, mountainSplices[i].first, mountainSplices[i + 1].first, 0.0f, 1.0f);
    const float height = mountainSplices[i + 1].second - mountainSplices[i].second;

    return hilliness * (mountainSplices[i].second + percent * height - Valley(pos) * val * 15.f);
}

float Terrain::Detail::Valley(const glm::vec2& pos) {
    auto val = Engine::Random::Simplex.fractal0_1(2, pos.x / VALLEY_F, pos.y / VALLEY_F);
    // shape of \\//
    val = std::abs(2.0f * val - 1.0f);

    return 1.0f - val;
}

float Terrain::Detail::Hilliness(const glm::vec2& pos) {
    const auto val = Engine::Random::Simplex.noise0_1(pos.x / HILLINESS_F, pos.y / HILLINESS_F);
    constexpr auto start = 0.4f, end = 0.8f;

    if (val < start) {
        return 0.0f;
    }

    if (val < end) {
        return Helpers::Math::Map(val, start, end, 0.0f, 1.0f);
    }

    return 1.0f;
}
