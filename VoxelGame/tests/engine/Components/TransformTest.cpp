#include "../../vendor/catch.hpp"

#include "engine/Components/Transform.h"
#include "helpers/Math.h"


TEST_CASE("transform component test", "[engine, transform, component]") {
    const Components::Transform comp(glm::vec3(0.0f));
    Components::Transform other(glm::vec3(0.25f));

    REQUIRE(Helpers::Math::Equal(comp.Position, glm::vec3(0.0f)));
    REQUIRE(Helpers::Math::Equal(comp.Scale, glm::vec3(1.0f)));

    REQUIRE(Helpers::Math::Equal(other.Position, glm::vec3(0.25f)));
    REQUIRE(Helpers::Math::Equal(other.Scale, glm::vec3(1.0f)));

    SECTION("component is inside other component") {
        SECTION("other is inside") {
            other.Scale = glm::vec3(0.1f);
            REQUIRE(comp.IsOtherInside(other));

            other.Position = glm::vec3(0.0f);
            REQUIRE(comp.IsOtherInside(other));

            other.Position = glm::vec3(0.35f);
            REQUIRE(comp.IsOtherInside(other));
        }

        SECTION("edge touching") {
            other.Scale = glm::vec3(0.5f);
            REQUIRE(comp.IsOtherInside(other));

            other.Position = glm::vec3(-0.25f);
            REQUIRE(comp.IsOtherInside(other));

            other.Position = glm::vec3(-0.25f, 0.25f, 0.0f);
            REQUIRE(comp.IsOtherInside(other));
        }

        SECTION("other component is partialy outside") {
            other.Scale = glm::vec3(0.5f);

            other.Position = glm::vec3(-0.3f);
            REQUIRE(!comp.IsOtherInside(other));

            other.Position = glm::vec3(-0.25f, 0.25f, 1.0f);
            REQUIRE(!comp.IsOtherInside(other));

            other.Scale = glm::vec3(0.6f);
            REQUIRE(!comp.IsOtherInside(other));

            other.Position = glm::vec3(-0.25f);
            REQUIRE(!comp.IsOtherInside(other));

            other.Position = glm::vec3(-0.25f, 0.25f, 0.0f);
            REQUIRE(!comp.IsOtherInside(other));
        }

        SECTION("other component is completely outside") {
            other.Scale = glm::vec3(0.5f);

            other.Position = glm::vec3(3.0f);
            REQUIRE(!comp.IsOtherInside(other));
        }

        SECTION("can be checked with game object") {
            GameObject go(glm::vec3(0.0f));

            REQUIRE(comp.IsOtherInside(go));
        }
    }
}
