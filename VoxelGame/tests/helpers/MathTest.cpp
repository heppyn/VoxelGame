#include "../vendor/catch.hpp"

#include <helpers/Math.h>

TEST_CASE("math tests", "[helpers, Math]") {
    using namespace Helpers;

    SECTION("Equal can compare floats") {
        REQUIRE(Math::Equal(2.0f, 2.0f));
        REQUIRE(Math::Equal(2.0f, 2.00009f));
        REQUIRE(Math::Equal(2.0f, 1.99999f));

        REQUIRE_FALSE(Math::Equal(2.0f, 3.0f));
        REQUIRE_FALSE(Math::Equal(2.0f, 2.1f));
        REQUIRE_FALSE(Math::Equal(2.0f, 1.9f));
    }

    SECTION("Equal can compare vec3") {
        REQUIRE(Math::Equal(glm::vec3(2.0f), glm::vec3(2.0f)));
        REQUIRE(Math::Equal(glm::vec3(2.0f), glm::vec3(2.0001f)));
        REQUIRE(Math::Equal(glm::vec3(2.0f, 3.0f, 4.0f), glm::vec3(2.0f, 3.0001f, 4.00001f)));

        REQUIRE_FALSE(Math::Equal(glm::vec3(2.0f, 3.0f, 4.0f), glm::vec3(3.0f, 3.0f, 4.0f)));
        REQUIRE_FALSE(Math::Equal(glm::vec3(2.0f, 3.0f, 4.0f), glm::vec3(2.0f, 4.0f, 4.0f)));
        REQUIRE_FALSE(Math::Equal(glm::vec3(2.0f, 3.0f, 4.0f), glm::vec3(2.0f, 3.0f, 5.0f)));

        REQUIRE_FALSE(Math::Equal(glm::vec3(2.0f, 3.0f, 4.0f), glm::vec3(3.0f, 4.0f, 5.0f)));
    }

    SECTION("Float can use Mod") {
        REQUIRE(Math::Mod(5.0f, 2) == 1);
        REQUIRE(Math::Mod(5.2f, 2) == 1);
        REQUIRE(Math::Mod(5.9f, 2) == 1);
        REQUIRE(Math::Mod(5.0f, 3) == 2);
        REQUIRE(Math::Mod(50.0f, 20) == 10);
    }

    SECTION("Can map ints") {
        REQUIRE(Math::Map(10, 0, 20, 0, 10) == 5);
        REQUIRE(Math::Map(10, 0, 20, 10, 20) == 15);
        REQUIRE(Math::Map(7, 0, 20, 0, 40) == 14);
    }

    SECTION("Can map floats") {
        REQUIRE(Math::Equal(Math::Map(3.0f, 0.0f, 6.0f, 0.0f, 1.0f), 0.5f));
        REQUIRE(Math::Equal(Math::Map(3.0f, 0.0f, 9.0f, 0.0f, 1.0f), 0.333333f));

        REQUIRE(Math::Equal(Math::Map(3.0f, 0.0f, 10.0f, 20.0f, 30.0f), 23.0f));
    }
    }