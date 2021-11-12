#include <iostream>

#include "../vendor/catch.hpp"

#include "engine/Random.h"

TEST_CASE("random test", "[engine, Random]") {
    SECTION("Generates random number from interval") {
        int same = 0;
        for (int i = 0; i < 20; ++i) {
            const auto r1 = Engine::Random::Get1dNoiseLimited(i, 3, 23);
            const auto r2 = Engine::Random::Get1dNoiseLimited(i, 3, 22);
            REQUIRE(r1 <= 3);
            REQUIRE(r2 <= 3);
            same += r1 == r2;
        }

        REQUIRE(same != 20);
    }
}
