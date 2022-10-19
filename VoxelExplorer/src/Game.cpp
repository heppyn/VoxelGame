#include "Game.h"

#include "vegetation/LSystemsManager.h"
#include "TerrainGen.h"
#include "ExampleScene.h"


App::~App() {
    Terrain::Vegetation::LSystemsManager::Clear();
}

void App::Init() {
    Game::Init();
    Terrain::Vegetation::LSystemsManager::Init();
#ifdef USE_TERRAIN_GEN
    Scene_.SetUpdateFunction(std::function<Chunk(const glm::vec2&)>(Terrain::TerrainGen::GenerateChunk));
#else
    Scene_.SetUpdateFunction(std::function<Chunk(const glm::vec2&)>(ExampleScene::LSystemTrees));
#endif

    InitScene();
    // move camera above terrain
    Camera->Position += glm::vec3(0.0f, Scene_.GetTerrainHeight(Camera->Position), 0.0f);
    Scene_.SetGlobalLight({ glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.7f) });
}