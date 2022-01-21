#include "ExampleScene.h"

#include <iostream>

#include "engine/GameObjectFactory.h"
#include "engine/Components/SpritesheetTex.h"
#include "engine/L-systems/LSystemExecutor.h"
#include "engine/L-systems/LSystemParser.h"


Chunk ExampleScene::EmptySides() {
    Chunk chunk(glm::vec2(0.0f));

    chunk.AddObject(GameObjectFactory::CreateObject({ 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }), Engine::Cube::PIPE);
    chunk.AddObject(GameObjectFactory::CreateObject({ 1.0f, 0.0f, 0.0f }, { 2.0f, 2.0f }),
      Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::TOP));

    chunk.AddObject(GameObjectFactory::CreateObject({ -0.5f, 0.0f, 0.0f }, { 1.0f, 1.0f }), Engine::Cube::PIPE);

    chunk.AddObject(GameObjectFactory::CreateObject({ -2.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
      Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::BOTTOM));

    chunk.AddObject(GameObjectFactory::CreateObject({ -3.5f, 0.0f, 0.0f }, { 2.0f, 2.0f }),
      Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::TOP));

    chunk.FinisChunk();
    return chunk;
}

Chunk ExampleScene::FaceCullingGrass() {
    Chunk chunk(glm::vec2(0.0f));

    chunk.AddObject(GameObjectFactory::CreateObject({ 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }), Engine::Cube::PIPE);
    chunk.AddObject(GameObjectFactory::CreateObject({ 1.0f, 0.0f, 0.0f }, { 2.0f, 2.0f }),
      Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::TOP));
    chunk.AddObject(GameObjectFactory::CreateObject({ 1.0f, 0.75f, 0.0f }, { 5.0f, 1.0f }, glm::vec3(0.5f)),
      Engine::Cube::BlockFaces::CreateBlockFaces(
        Engine::Cube::Faces::BOTTOM,
        Engine::Cube::Faces::FRONT,
        Engine::Cube::Faces::BACK,
        Engine::Cube::Faces::LEFT,
        Engine::Cube::Faces::RIGHT));

    chunk.AddObject(GameObjectFactory::CreateObject({ 2.5f, 0.0f, 0.0f }, { 1.0f, 1.0f }), Engine::Cube::PIPE);
    chunk.AddObject(GameObjectFactory::CreateObject({ 2.5f, 0.0f, 0.0f }, { 2.0f, 2.0f }),
      Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::TOP));
    chunk.AddObject(GameObjectFactory::CreateObject({ 2.5f, 0.75f, 0.0f }, { 5.0f, 1.0f }, glm::vec3(0.5f)), Engine::Cube::PIPE);

    chunk.FinisChunk();
    return chunk;
}

Chunk ExampleScene::AlphaBlendingGrass() {
    Chunk chunk(glm::vec2(0.0f));

    chunk.AddObject(GameObjectFactory::CreateObject({ 2.0f, 0.0f, 0.0f }, { 2.0f, 2.0f }),
      Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::TOP));
    chunk.AddObject(GameObjectFactory::CreateObject({ 2.0f, 0.75f, 0.0f }, { 5.0f, 1.0f }, glm::vec3(0.5f)), Engine::Cube::PIPE);
    chunk.AddObject(GameObjectFactory::CreateObject({ 2.0f, 0.0f, 0.0f }, { 2.0f, 2.0f }), Engine::Cube::PIPE);

    chunk.AddObject(GameObjectFactory::CreateObject({ 1.0f, 0.0f, 0.0f }, { 2.0f, 2.0f }));
    chunk.AddObject(GameObjectFactory::CreateObject({ 1.0f, 0.75f, 0.0f }, { 5.0f, 1.0f }, glm::vec3(0.5f)), Engine::Cube::PIPE);

    chunk.FinisChunk();
    return chunk;
}

Chunk ExampleScene::LSystemGrass() {
    LSystems::LSystemExecutor ge(0, 0.0f);
    Chunk chunk(glm::vec2(0.0f));
    const auto lSystems = LSystems::LSystemParser::LoadLSystemFromFile("./res/l-systems/plants/Grass2D.txt");
    if (!lSystems.empty()) {
        auto pos = glm::vec3(0.0f);
        for (const auto& lSystem : lSystems) {
            auto objects = ge.GenerateBasedOn(pos, lSystem, 0.3f, 5, Engine::Random::GetNoise(pos));
            for (auto& o : objects[0]) {
                o.AddComponent<Components::SpritesheetTex>(glm::vec2(1.0f, 0.0f));
            }
            chunk.GetObjects()[Chunk::DefaultCube_].insert(
              chunk.GetObjects()[Chunk::DefaultCube_].end(),
              std::make_move_iterator(objects[0].begin()),
              std::make_move_iterator(objects[0].end()));

            pos += glm::vec3(10.0f, 0.0f, 0.0f);
        }
        chunk.FinisChunk();
    }
    else {
        std::cout << "Failed to load L-system\n";
    }

    return chunk;
}

Chunk ExampleScene::PhongLight() {
    Chunk chunk(glm::vec2(0.0f));

    for (int i = -30; i < 30; ++i) {
        for (int j = -30; j < 30; ++j) {
            chunk.AddObject(GameObjectFactory::CreateObject(
                { static_cast<float>(i), 0.0f, static_cast<float>(j) },
                { 0.0f, 5.0f }));
        }
    }

    chunk.FinisChunk();
    return chunk;
}
