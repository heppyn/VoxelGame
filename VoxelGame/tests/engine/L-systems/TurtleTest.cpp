#include "../../vendor/catch.hpp"

#include "engine/L-systems/Turtle.h"
#include "helpers/Math.h"
#include "helpers/Print.h"


TEST_CASE("turtle test", "[engine, turtle]") {
    // setup
    LSystems::Detail::Turtle turtle(glm::vec3(0.0f));
    REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f)));

    SECTION("turtle can move forward") {
        turtle.MoveForward();
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 0.0f, -1.0f)));

        turtle.MoveForward(3.0f);
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 0.0f, -4.0f)));
    }

    SECTION("turtle can move backwards") {
        turtle.MoveBackward();
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 0.0f, 1.0f)));

        turtle.MoveBackward(2.0f);
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 0.0f, 3.0f)));
    }

    SECTION("turtle can move sideways") {
        turtle.MoveSide();
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(1.0f, 0.0f, 0.0f)));

        turtle.MoveSide(3.0f);
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(4.0f, 0.0f, 0.0f)));

        turtle.MoveSide(-5.0f);
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(-1.0f, 0.0f, 0.0f)));
    }

    SECTION("turtle can move upwards") {
        turtle.MoveUp();
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 1.0f, 0.0f)));

        turtle.MoveUp(3.0f);
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 4.0f, 0.0f)));
    }

    SECTION("turtle can move downwards") {
        turtle.MoveDown();
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, -1.0f, 0.0f)));

        turtle.MoveDown(2.0f);
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, -3.0f, 0.0f)));
    }

    SECTION("turtle can move") {
        constexpr auto offset = glm::vec3(0.0f, 3.0f, 0.0f);
        turtle.Move(offset);

        REQUIRE(Helpers::Math::Equal(turtle.Position(), offset));
    }

    SECTION("turtle can change yaw 90 degrees and move") {
        turtle.Rotate(90.0f, 0.0f);
        turtle.MoveForward(1.0f);

        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(1.0f, 0.0f, 0.0f)));

        turtle.Rotate(90.0f, 0.0f);
        turtle.MoveForward(1.0f);

        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(1.0f, 0.0f, 1.0f)));
    }

    SECTION("turtle can change pitch 90 degrees and move") {
        turtle.Rotate(0.0f, 90.0f);
        turtle.MoveForward(1.0f);

        INFO("Turtle position: " << Helpers::ToString(turtle.Position()));
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 1.0f, 0.0f)));

        turtle.Rotate(0.0f, -180.0f);
        turtle.MoveForward(2.0f);

        INFO("Turtle position: " << Helpers::ToString(turtle.Position()));
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, -1.0f, 0.0f)));
    }

    SECTION("turtle can rotate on both axes and move") {
        turtle.Rotate(90.0f, 90.0f);
        turtle.MoveForward(1.0f);
        turtle.MoveSide(1.0f);

        INFO("Turtle position: " << Helpers::ToString(turtle.Position()));
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 1.0f, 1.0f)));

        turtle.Rotate(0.0f, -90.0f);
        turtle.MoveForward(1.0f);
        turtle.MoveSide(1.0f);
        INFO("Turtle position: " << Helpers::ToString(turtle.Position()));
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(1.0f, 1.0f, 2.0f)));
    }

    SECTION("turtle can yaw by arbitrary angle") {
        turtle.Rotate(45.0f, 0.0f);
        turtle.MoveForward(sqrtf(2.0f));

        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(1.0f, 0.0f, -1.0f)));

        LSystems::Detail::Turtle t1(glm::vec3(0.0f));
        t1.Rotate(30.0f, 0.0f);
        t1.MoveForward(sqrtf(1.0f));

        INFO("Turtle position: " << Helpers::ToString(t1.Position()));
        REQUIRE(Helpers::Math::Equal(t1.Position(), glm::vec3(0.5f, 0.0f, -sqrtf(3.0f) / 2)));
    }

    SECTION("turtle can rotate around x axis") {
        turtle.Rotate(0.0f, 90.0f);
        turtle.MoveForward(1.0f);

        INFO("Turtle position: " << Helpers::ToString(turtle.Position()));
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 1.0f, 0.0f)));

        turtle.Rotate(0.0f, 90.0f);
        turtle.MoveForward(1.0f);

        INFO("Turtle position: " << Helpers::ToString(turtle.Position()));
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 1.0f, 1.0f)));

        turtle.Rotate(0.0f, 90.0f);
        turtle.MoveForward(1.0f);

        INFO("Turtle position: " << Helpers::ToString(turtle.Position()));
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 0.0f, 1.0f)));

        turtle.Rotate(0.0f, 90.0f);
        turtle.MoveForward(1.0f);

        INFO("Turtle position: " << Helpers::ToString(turtle.Position()));
        REQUIRE(Helpers::Math::Equal(turtle.Position(), glm::vec3(0.0f, 0.0f, 0.0f)));
    }
}
