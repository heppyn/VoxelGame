#include "../vendor/catch.hpp"

#include "engine/GameObject.h"
#include "engine/Components/Transform.h"
#include "engine/Components/SpritesheetTex.h"
#include "helpers/Math.h"

TEST_CASE("game object tests", "[engine, GameObject]") {
    SECTION("Component can be added") {
        GameObject go;
        go.AddComponent<Components::Transform>();

        REQUIRE(go.HasComponent<Components::Transform>());
    }

    SECTION("Component can be retrieved") {
        GameObject go;
        go.AddComponent<Components::Transform>(glm::vec3(1.0f));

        REQUIRE(Helpers::Math::Equal(go.GetComponent<Components::Transform>().Position, glm::vec3(1.0f)));
    }

    SECTION("Game object can be created with position") {
        const GameObject go(glm::vec3(1.0f));

        REQUIRE(go.HasComponent<Components::Transform>());
    }

    SECTION("Game object can be created with position and texture") {
        const GameObject go(glm::vec3(1.0f), glm::vec2(0.0f));

        REQUIRE(go.HasComponent<Components::Transform>());
        REQUIRE(go.HasComponent<Components::SpritesheetTex>());
    }

    SECTION("Game object has position") {
        const GameObject go(glm::vec3(1.0f));

        REQUIRE(Helpers::Math::Equal(go.Position(), glm::vec3(1.0f)));
    }

    SECTION("Game object can be moved") {
        GameObject go(glm::vec3(1.0f));
        go.Move({ 1.0f, 0.0f, 0.0f });

        REQUIRE(Helpers::Math::Equal(go.Position(), glm::vec3(2.0f, 1.0f, 1.0f)));
    }

    SECTION("Game object has scale") {
        const GameObject go(glm::vec3(1.0f));

        REQUIRE(Helpers::Math::Equal(go.Scale(), glm::vec3(1.0f)));
    }

    SECTION("Game object be scaled") {
        GameObject go(glm::vec3(1.0f));
        go.Scale(glm::vec3(0.5));

        REQUIRE(Helpers::Math::Equal(go.Scale(), glm::vec3(0.5f)));
    }
}