#include "../vendor/catch.hpp"

#include "engine/GameObjectFactory.h"
#include "helpers/Print.h"

TEST_CASE("game object factory test", "[engine, GameObjectFactory]") {
    SECTION("Game object can be created") {
        const auto go = GameObjectFactory::CreateObject({ 1.0f, 2.0f, 3.0f }, { 0.0f, 0.0f });

        REQUIRE(go.Scale() == glm::vec3(1.0f));
        REQUIRE(go.Position() == glm::vec3(1.0f, 2.0f, 3.0f));
    }

    SECTION("Game object can be created from defult preset") {
        GameObjectFactory GOFactory;

        const auto go = GOFactory.CreateFromPreset({ 1.0f, 2.0f, 3.0f }, { 0.0f, 0.0f });
        REQUIRE(go.Scale() == glm::vec3(1.0f));
        REQUIRE(go.Position() == glm::vec3(1.0f, 2.0f, 3.0f));
    }

    SECTION("Game object can be created from preset") {
        GameObjectFactory GOFactory(glm::vec3(0.5f), { 0.0f, 1.0f, 0.0f });

        const auto go = GOFactory.CreateFromPreset({ 1.0f, 2.0f, 3.0f }, { 0.0f, 0.0f });
        REQUIRE(go.Scale() == glm::vec3(0.5f));
        REQUIRE(go.Position() == glm::vec3(1.0f, 3.0f, 3.0f));
    }

    SECTION("Game object can be created stacked on top of each other") {
        GameObjectFactory GOFactory(glm::vec3(0.5f), { 0.0f, -0.25f, 0.0f });

        auto go = GOFactory.CreateStacked({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f });
        REQUIRE(go.Scale() == glm::vec3(0.5f));
        INFO("Block position " << Helpers::ToString(go.Position()));
        REQUIRE(go.Position() == glm::vec3(0.0f, -0.25f, 0.0f));

        go = GOFactory.CreateStacked({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f });
        REQUIRE(go.Scale() == glm::vec3(0.5f));
        INFO("Block position " << Helpers::ToString(go.Position()));
        REQUIRE(go.Position() == glm::vec3(0.0f, 0.25f, 0.0f));

        go = GOFactory.CreateStacked({ 0.0f, 2.0f, 0.0f }, { 0.0f, 0.0f });
        REQUIRE(go.Scale() == glm::vec3(0.5f));
        INFO("Block position " << Helpers::ToString(go.Position()));
        REQUIRE(go.Position() == glm::vec3(0.0f, 0.75f, 0.0f));
    }

    SECTION("Game object can be created scaled") {
        auto go = GameObjectFactory::CreateObject({ 1.0f, 2.0f, 3.0f }, { 0.0f, 0.0f }, glm::vec3(0.5f));

        REQUIRE(go.Scale() == glm::vec3(0.5f));
        REQUIRE(go.Position() == glm::vec3(1.0f, 2.0f, 3.0f));

        go = GameObjectFactory::CreateObject({ 1.0f, 2.0f, 3.0f }, { 0.0f, 0.0f }, 0.5f);

        REQUIRE(go.Scale() == glm::vec3(0.5f));
        REQUIRE(go.Position() == glm::vec3(1.0f, 2.0f, 3.0f));
    }
}
