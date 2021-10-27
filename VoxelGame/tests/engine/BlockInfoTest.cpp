#include "../vendor/catch.hpp"

#include "engine/BlockInfo.h"
#include "helpers/Math.h"

TEST_CASE("block info test", "[engine, block_info]") {
    BlockInfo blockInfo;

    // check defaults
    REQUIRE_FALSE(blockInfo.HasTree());
    REQUIRE(Helpers::Math::Equal(blockInfo.GetSurfaceHeight(), 0.0f));
    REQUIRE(blockInfo.GetBiome() == 0u);

    SECTION("add tree") {
        blockInfo.AddTree();
        REQUIRE(blockInfo.HasTree());
    }

    SECTION("change surface height") {
        blockInfo.SetSurfaceHeight(255.0f);
        REQUIRE(Helpers::Math::Equal(blockInfo.GetSurfaceHeight(), 255.0f));

        blockInfo.SetSurfaceHeight(5.0f);
        REQUIRE(Helpers::Math::Equal(blockInfo.GetSurfaceHeight(), 5.0f));
    }

    SECTION("change biome") {
        blockInfo.SetBiome(1);
        REQUIRE(blockInfo.GetBiome() == 1u);

        blockInfo.SetBiome(7);
        REQUIRE(blockInfo.GetBiome() == 7u);

        blockInfo.SetBiome(5);
        REQUIRE(blockInfo.GetBiome() == 5u);
    }
}
