#include "../../vendor/catch.hpp"

#include "engine/L-systems/LSystemExecutor.h"
#include "helpers/Math.h"
#include "helpers/Print.h"

TEST_CASE("L-system executor test", "[engine, LSystemExecutor]") {
    LSystems::LSystemExecutor executor(0.0f);

    SECTION("executor can execute simple L-system") {
        LSystems::Detail::RandomGrammar grammar("U");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = std::move(executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 1.0f, 0, 1)[0]);

        REQUIRE(objects.size() == 1);
        REQUIRE(Helpers::Math::Equal(objects[0].Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
    }

    SECTION("executor anchors game object to the bottom") {
        LSystems::Detail::RandomGrammar grammar("U");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = std::move(executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 0.5f, 0, 1)[0]);

        REQUIRE(objects.size() == 1);
        INFO(Helpers::ToString(objects[0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[0].Position(), glm::vec3(0.0f, -0.25f, 0.0f)));
    }

    SECTION("executor can stack object that are shrinked") {
        LSystems::Detail::RandomGrammar grammar("UxU");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = std::move(executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 0.5f, 0, 1)[0]);

        REQUIRE(objects.size() == 3);
        INFO("Object 0 " << Helpers::ToString(objects[0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[0].Position(), glm::vec3(0.0f, -0.25f, 0.0f)));
        INFO("Object 1 " << Helpers::ToString(objects[1].Position()));
        REQUIRE(Helpers::Math::Equal(objects[1].Position(), glm::vec3(0.0f, 0.125f, 0.0f)));
        INFO("Object 2 " << Helpers::ToString(objects[2].Position()));
        REQUIRE(Helpers::Math::Equal(objects[2].Position(), glm::vec3(0.0f, 0.25f + 0.125f, 0.0f)));
    }

    SECTION("executor can stack object that are shrinked and enlarged") {
        LSystems::Detail::RandomGrammar grammar("UxUXU");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = std::move(executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 0.5f, 0, 1)[0]);

        REQUIRE(objects.size() == 4);
        INFO("Object 0 " << Helpers::ToString(objects[0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[0].Position(), glm::vec3(0.0f, -0.25f, 0.0f)));

        INFO("Object 3 " << Helpers::ToString(objects[3].Position()));
        REQUIRE(Helpers::Math::Equal(objects[3].Position(), glm::vec3(0.0f, 0.75f, 0.0f)));
    }

    SECTION("executor can stack objects that are shrink a then set to the oroginal size") {
        LSystems::Detail::RandomGrammar grammar("UxxUSU");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = std::move(executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 0.5f, 0, 1)[0]);

        REQUIRE(objects.size() == 6);
        INFO("Object 0 " << Helpers::ToString(objects[0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[0].Position(), glm::vec3(0.0f, -0.25f, 0.0f)));
        INFO("Object 1 " << Helpers::ToString(objects[1].Position()));
        REQUIRE(Helpers::Math::Equal(objects[1].Position(), glm::vec3(0.0f, 0.125f / 2.0f, 0.0f)));

        INFO("Object 5 " << Helpers::ToString(objects[5].Position()));
        REQUIRE(Helpers::Math::Equal(objects[5].Position(), glm::vec3(0.0f, 4.0f * 0.125f + 0.25f, 0.0f)));
    }

    SECTION("executor can create objects when turtle rotates") {
        LSystems::Detail::RandomGrammar grammar("U&&U^^U");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = std::move(executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 1.0f, 0, 1)[0]);

        REQUIRE(objects.size() == 3);
        INFO("Object 0 " << Helpers::ToString(objects[0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[0].Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
        INFO("Object 1 " << Helpers::ToString(objects[1].Position()));
        REQUIRE(Helpers::Math::Equal(objects[1].Position(), glm::vec3(0.0f, 1.0f, 0.0f)));
        INFO("Object 2 " << Helpers::ToString(objects[2].Position()));
        REQUIRE(Helpers::Math::Equal(objects[2].Position(), glm::vec3(0.0f, 1.0f, 1.0f)));
    }

    SECTION("executor can generate models with multiple parts") {
        LSystems::Detail::RandomGrammar grammar("U1U");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 1.0f, 0, 1);

        REQUIRE(objects.size() == 2);
        REQUIRE(objects[0].size() == 1);
        REQUIRE(objects[1].size() == 1);
        INFO("Object 0 " << Helpers::ToString(objects[0][0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[0][0].Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
        INFO("Object 1 " << Helpers::ToString(objects[1][0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[1][0].Position(), glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    SECTION("executor can generate models with maximum nuber of parts") {
        LSystems::Detail::RandomGrammar grammar("U9U");
        const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

        const auto objects = executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 1.0f, 0, 1);

        REQUIRE(objects.size() == 10);
        REQUIRE(objects[0].size() == 1);
        REQUIRE(objects[5].empty());
        REQUIRE(objects[9].size() == 1);
        INFO("Object 0 " << Helpers::ToString(objects[0][0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[0][0].Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
        INFO("Object 9 " << Helpers::ToString(objects[9][0].Position()));
        REQUIRE(Helpers::Math::Equal(objects[9][0].Position(), glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    SECTION("executor can delete parts of the model that overlap") {
        SECTION("one overlaps") {
            LSystems::Detail::RandomGrammar grammar("[U][1U]");
            const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

            const auto objects = executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 1.0f, 0, 1);

            REQUIRE(objects.size() == 2);
            REQUIRE(objects[0].empty());
            REQUIRE(objects[1].size() == 1);

            INFO("Object 0 " << Helpers::ToString(objects[1][0].Position()));
            REQUIRE(Helpers::Math::Equal(objects[1][0].Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
        }

        SECTION("two overlaps") {
            LSystems::Detail::RandomGrammar grammar("U[xU][1U]");
            const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

            const auto objects = executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 1.0f, 0, 1);

            REQUIRE(objects.size() == 2);
            REQUIRE(objects[0].size() == 1);
            REQUIRE(objects[1].size() == 1);

            INFO("Object 0 0 " << Helpers::ToString(objects[0][0].Position()));
            REQUIRE(Helpers::Math::Equal(objects[0][0].Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
            INFO("Object 1 0 " << Helpers::ToString(objects[1][0].Position()));
            REQUIRE(Helpers::Math::Equal(objects[1][0].Position(), glm::vec3(0.0f, 1.0f, 0.0f)));
        }

        SECTION("no overlap between buffers 0 and 1") {
            LSystems::Detail::RandomGrammar grammar("[U][U1U]");
            const LSystems::LSystem lSystem(std::move(grammar), 45.0f, 45.f, 0.5f);

            const auto objects = executor.GenerateBasedOn(glm::vec3(0.0f), lSystem, 1.0f, 0, 1);

            REQUIRE(objects.size() == 2);
            REQUIRE(objects[0].size() == 2);
            REQUIRE(objects[1].size() == 1);

            INFO("Object 0 0" << Helpers::ToString(objects[0][0].Position()));
            REQUIRE(Helpers::Math::Equal(objects[0][0].Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
            INFO("Object 0 1" << Helpers::ToString(objects[0][1].Position()));
            REQUIRE(Helpers::Math::Equal(objects[0][1].Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
            INFO("Object 1 0" << Helpers::ToString(objects[1][0].Position()));
            REQUIRE(Helpers::Math::Equal(objects[1][0].Position(), glm::vec3(0.0f, 1.0f, 0.0f)));
        }
    }
}
