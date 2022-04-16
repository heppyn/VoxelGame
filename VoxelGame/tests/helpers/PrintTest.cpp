#include "../vendor/catch.hpp"

#include <helpers/Print.h>

TEST_CASE("print tests", "[helpers, Print]") {
    using namespace Helpers;

    SECTION("Can convert vector to string") {
        REQUIRE(ToString(glm::vec2(1.0f, 2.0f)) == "(1, 2)");
        REQUIRE(ToString(glm::vec3(1.0f, 2.0f, 3.0f)) == "(1, 2, 3)");
        REQUIRE(ToString(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f)) == "(1, 2, 3, 4)");

        REQUIRE(ToString(glm::vec2(1.11f, 2.22f)) == "(1.11, 2.22)");
    }

    SECTION("Can convert matrix to string") {
        REQUIRE(ToString(glm::mat4(1.0f)) == "[[1, 0, 0, 0]\n [0, 1, 0, 0]\n [0, 0, 1, 0]\n [0, 0, 0, 1]]\n");
    }

    SECTION("Can convert block info to json") {
        BlockInfo blockInfo;
        blockInfo.AddTree();
        blockInfo.SetBiome(1u);
        blockInfo.SetHumidity(2u);
        blockInfo.SetSurfaceHeight(20.0f);
        blockInfo.SetTemperature(3u);

        REQUIRE(ToJson(blockInfo) == "{\"tree\":1,\"hum\":2,\"tem\":3,\"biome\":1,\"height\":20}");
    }
}