#include "../../vendor/catch.hpp"

#include "engine/L-systems/LSystemExecutor.h"
#include "helpers/Math.h"
#include "helpers/Print.h"

TEST_CASE("L-system executor test", "[engine, LSystemExecutor]") {
    LSystems::LSystemExecutor executor(0.0f);

    SECTION("executor can execute simple L-system") {
        LSystems::Detail::RandomGrammar grammar("U");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 1.0f, 0, 1);

        REQUIRE(objects.size() == 1);
        REQUIRE(Helpers::Math::Equal(objects[0].Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
    }

    SECTION("executor anchors game object to the bottom") {
        LSystems::Detail::RandomGrammar grammar("U");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 0.5f, 0, 1);

        REQUIRE(objects.size() == 1);
        INFO(Helpers::ToString(objects[0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[0].Position(), glm::vec3(0.0f, -0.25f, 0.0f)));
    }

    SECTION("executor can stack object that are shrinked") {
        LSystems::Detail::RandomGrammar grammar("UXU");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 0.5f, 0, 1);

        REQUIRE(objects.size() == 3);
        INFO("Object 0 " << Helpers::ToString(objects[0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[0].Position(), glm::vec3(0.0f, -0.25f, 0.0f)));
        INFO("Object 1 " << Helpers::ToString(objects[1].Position()));
        REQUIRE(Helpers::Math::Equal(objects[1].Position(), glm::vec3(0.0f, 0.125f, 0.0f)));
        INFO("Object 2 " << Helpers::ToString(objects[2].Position()));
        REQUIRE(Helpers::Math::Equal(objects[2].Position(), glm::vec3(0.0f, 0.25f + 0.125f, 0.0f)));
    }

    SECTION("executor can create objects when turtle rotates") {
        LSystems::Detail::RandomGrammar grammar("U&&U^^U");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 1.0f, 0, 1);

        REQUIRE(objects.size() == 3);
        INFO("Object 0 " << Helpers::ToString(objects[0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[0].Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
        INFO("Object 1 " << Helpers::ToString(objects[1].Position()));
        REQUIRE(Helpers::Math::Equal(objects[1].Position(), glm::vec3(0.0f, 1.0f, 0.0f)));
        INFO("Object 2 " << Helpers::ToString(objects[2].Position()));
        REQUIRE(Helpers::Math::Equal(objects[2].Position(), glm::vec3(0.0f, 1.0f, 1.0f)));
    }
}