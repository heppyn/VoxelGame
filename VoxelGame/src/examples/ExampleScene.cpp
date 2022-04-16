#include "ExampleScene.h"

#include <iostream>

#include "engine/GameObjectFactory.h"
#include "engine/Components/SpritesheetTex.h"
#include "engine/L-systems/LSystemExecutor.h"
#include "engine/L-systems/LSystemParser.h"
#include "engine/Random.h"
#include "game/vegetation/GrassFactory.h"
#include "game/vegetation/Tree.h"
#include "game/vegetation/TreeFactory.h"


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

Chunk ExampleScene::Shadow() {
    Chunk chunk(glm::vec2(0.0f));

    constexpr int size = 50;
    for (int i = -size; i < size; ++i) {
        for (int j = -size; j < size; ++j) {
            chunk.AddObject(GameObjectFactory::CreateObject(
              { static_cast<float>(i), 0.0f, static_cast<float>(j) },
              { 0.0f, 5.0f }));
        }
    }

    chunk.AddObject(GameObjectFactory::CreateObject({ 0.0f, 5.0f, 0.0f }, { 2.0f, 2.0f }));
    chunk.AddObject(GameObjectFactory::CreateObject({ 1.0f, 5.0f, 0.0f }, { 2.0f, 2.0f }));
    chunk.AddObject(GameObjectFactory::CreateObject({ -10.0f, 5.0f, 0.0f }, { 2.0f, 2.0f }));
    chunk.AddObject(GameObjectFactory::CreateObject({ -20.0f, 5.0f, -1.0f }, { 2.0f, 2.0f }));
    chunk.AddObject(GameObjectFactory::CreateObject({ -30.0f, 5.0f, -2.0f }, { 2.0f, 2.0f }));
    chunk.AddObject(GameObjectFactory::CreateObject({ 10.0f, 5.0f, 1.0f }, { 2.0f, 2.0f }));
    chunk.AddObject(GameObjectFactory::CreateObject({ 20.0f, 5.0f, 3.0f }, { 2.0f, 2.0f }));
    chunk.AddObject(GameObjectFactory::CreateObject({ 30.0f, 5.0f, 5.0f }, { 2.0f, 2.0f }));

    chunk.FinisChunk();
    return chunk;
}

Chunk ExampleScene::RandomNoiseTerrain() {
    Chunk chunk(glm::vec2(0.0f));

    for (unsigned i = 0; i < 200; ++i) {
        for (unsigned j = 0; j < 200; ++j) {
            const auto height = Engine::Random::Get2dNoiseLimited(i, j, 8);
            for (unsigned h = 0; h < height; ++h) {
                chunk.AddObject(GameObjectFactory::CreateObject(
                  { i, h, j },
                  { 0.0f, 1.0f }));
            }
            chunk.AddObject(GameObjectFactory::CreateObject({ i, height, j }, { 1.0f, 1.0f }), Engine::Cube::PIPE);
            chunk.AddObject(GameObjectFactory::CreateObject({ i, height, j }, { 2.0f, 2.0f }),
              Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::TOP));
        }
    }

    chunk.FinisChunk();
    return chunk;
}

Chunk ExampleScene::PerlinSimplexTerrain() {
    Chunk chunk(glm::vec2(0.0f));
    constexpr auto freq = 20.0f;

    for (unsigned i = 0; i < 100; ++i) {
        for (unsigned j = 0; j < 200; ++j) {
            const auto heightPer = static_cast<unsigned>(Engine::Random::Perlin.noise2D_0_1(static_cast<float>(i) / freq, static_cast<float>(j) / freq) * 8.0f);
            const auto heightSim = static_cast<unsigned>(Engine::Random::Simplex.noise0_1(static_cast<float>(i) / freq, static_cast<float>(j) / freq) * 8.0f);
            for (unsigned h = 0; h < heightPer; ++h) {
                chunk.AddObject(GameObjectFactory::CreateObject(
                  { i, h, j },
                  { 0.0f, 1.0f }));
            }
            glm::vec3 pos = { i, heightPer, j };
            chunk.AddObjectData(Terrain::Vegetation::TreeFactory::GenerateTree(pos, Terrain::BiomeType::Grassland));
            auto grass = Terrain::Vegetation::GrassFactory::GenerateGrass(pos, Terrain::BiomeType::Grassland);
            chunk.AddObjectsTrans(std::move(grass), Terrain::Vegetation::GrassFactory::GrassCube());

            chunk.AddObject(GameObjectFactory::CreateObject(pos, { 1.0f, 1.0f }), Engine::Cube::PIPE);
            chunk.AddObject(GameObjectFactory::CreateObject(pos, { 2.0f, 2.0f }),
              Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::TOP));

            for (unsigned h = 0; h < heightSim; ++h) {
                chunk.AddObject(GameObjectFactory::CreateObject(
                  { i + 100, h, j },
                  { 0.0f, 1.0f }));
            }
            pos = { i + 100, heightSim, j };
            chunk.AddObjectData(Terrain::Vegetation::TreeFactory::GenerateTree(pos, Terrain::BiomeType::Grassland));
            grass = Terrain::Vegetation::GrassFactory::GenerateGrass(pos, Terrain::BiomeType::Grassland);
            chunk.AddObjectsTrans(std::move(grass), Terrain::Vegetation::GrassFactory::GrassCube());

            chunk.AddObject(GameObjectFactory::CreateObject(pos, { 1.0f, 1.0f }), Engine::Cube::PIPE);
            chunk.AddObject(GameObjectFactory::CreateObject(pos, { 2.0f, 2.0f }),
              Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::TOP));
        }
    }

    chunk.FinisChunk();
    return chunk;
}

Chunk ExampleScene::TreeDistribution() {
    Chunk chunk(glm::vec2(0.0f));

    for (unsigned i = 0; i < 200; ++i) {
        constexpr auto freq = 5.0f;
        const auto height = static_cast<unsigned>(Engine::Random::Perlin.noise1D_0_1(static_cast<float>(i) / freq) * 20.0f);
        for (unsigned h = 0; h <= height; ++h) {
            chunk.AddObject(GameObjectFactory::CreateObject(
              { i, h, 0.0f },
              { 6.0f, 4.0f }));
        }

        if (height > static_cast<unsigned>(Engine::Random::Perlin.noise1D_0_1(static_cast<float>(i - 1) / freq) * 20.0f)
            && height > static_cast<unsigned>(Engine::Random::Perlin.noise1D_0_1(static_cast<float>(i + 1) / freq) * 20.0f)) {
            chunk.AddObjects(Terrain::Vegetation::Tree::SpawnCactus({ i, height, 0.0f }));
        }
    }

    chunk.FinisChunk();
    return chunk;
}
