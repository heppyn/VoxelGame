#include "../vendor/catch.hpp"

#include "engine/BlockFaces.h"

TEST_CASE("Block faces test", "[engine, block_faces]") {
    SECTION("Can be created with all types of faces") {
        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::ALL).Value == 0b00111111);
        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::TOP).Value == 0b00100000);
        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::BOTTOM).Value == 0b00010000);
        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::FRONT).Value == 0b00001000);
        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::BACK).Value == 0b00000100);
        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::LEFT).Value == 0b00000010);
        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::RIGHT).Value == 0b00000001);
    }

    SECTION("Can be created with multiple faces") {
        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(
                  Engine::Cube::Faces::FRONT,
                  Engine::Cube::Faces::BACK,
                  Engine::Cube::Faces::LEFT,
                  Engine::Cube::Faces::RIGHT)
                  .Value
                == 0b00001111);

        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(
                  Engine::Cube::Faces::TOP,
                  Engine::Cube::Faces::BOTTOM)
                  .Value
                == 0b00110000);
    }

    SECTION("Can be created with all faces") {
        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(
                  Engine::Cube::Faces::BACK,
                  Engine::Cube::Faces::FRONT,
                  Engine::Cube::Faces::TOP,
                  Engine::Cube::Faces::BOTTOM,
                  Engine::Cube::Faces::LEFT,
                  Engine::Cube::Faces::RIGHT)
                  .Value
                == 0b00111111);
    }

    SECTION("Can be compared") {
        REQUIRE(Engine::Cube::BlockFaces::CreateBlockFaces(
                  Engine::Cube::Faces::BACK,
                  Engine::Cube::Faces::FRONT,
                  Engine::Cube::Faces::TOP,
                  Engine::Cube::Faces::BOTTOM,
                  Engine::Cube::Faces::LEFT,
                  Engine::Cube::Faces::RIGHT)
                == Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::ALL));
    }

    SECTION("Can be ordered") {
        REQUIRE(
          Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::ALL)
          > Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::FRONT));
    }
}
