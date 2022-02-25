#include <iostream>

#include "../vendor/catch.hpp"

#include "engine/Scene.h"
#include "helpers/Print.h"

TEST_CASE("scene test", "[engine, Scene]") {
    const auto view = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    const auto proj = glm::perspective(
      glm::radians(45.0f),
      1.0f,
      0.1f,
      500.0f);
    const auto viewProj = proj * view;

    SECTION("Position is in view") {
        REQUIRE(Scene::IsChunkInView({ 0.0f, 0.0f, -16.0f }, viewProj));
        REQUIRE(Scene::IsChunkInView({ 0.0f, 0.0f, -32.0f }, viewProj));
        REQUIRE(Scene::IsChunkInView({ 0.0f, 0.0f, -48.0f }, viewProj));
    }

    SECTION("Only one position is in view") {
        REQUIRE(Scene::IsChunkInView({ 0.0f, 0.0f, -32.0f }, viewProj));

        REQUIRE_FALSE(Scene::IsChunkInView({ 0.0f, 0.0f, 32.0f }, viewProj));
        REQUIRE_FALSE(Scene::IsChunkInView({ 32.0f, 0.0f, 0.0f }, viewProj));
        REQUIRE_FALSE(Scene::IsChunkInView({ -32.0f, 0.0f, 0.0f }, viewProj));
    }

    SECTION("Position above player is not in view") {
        REQUIRE_FALSE(Scene::IsChunkInView({ 0.0f, 64.0f, 0.0f }, viewProj));
    }
}
