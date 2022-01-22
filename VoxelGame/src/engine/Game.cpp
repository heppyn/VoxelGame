#include "Game.h"

#include "ResourceManager.h"
#include "game/vegetation/LSystemsManager.h"
#include "../open_gl/WindowManagerGl.h"
#include "../helpers/Constants.h"
#include "Random.h"
#include "engine/files/Export.h"


Game::~Game() {
    ResourceManager::Clear();
    Terrain::Vegetation::LSystemsManager::Clear();
}

void Game::Init() {
    ResourceManager::LoadShader("./res/shaders/LightBatch.vert", "./res/shaders/Light.frag", nullptr, "lightBatch");
    ResourceManager::LoadShader("./res/shaders/Mesh.vert", "./res/shaders/Mesh.frag", nullptr, "meshShader");
    ResourceManager::LoadShader("./res/shaders/Shadow.vert", "./res/shaders/Shadow.frag", nullptr, "depth");

    ResourceManager::LoadTexture2D("./res/textures/white.png", true, "white");
    ResourceManager::LoadTexture2D(Constants::VOXEL_PACK_PATH_SH + "sprite_sheet.png", true, Constants::SPRITE_SHEET);
    ResourceManager::LoadTexture2D(Constants::VOXEL_PACK_PATH_SH + "sprite_sheet.png", true, Constants::SPRITE_SHEET_SPEC)->SetTypeSpecular();
    //ResourceManager::LoadTexture2D("./res/textures/atlas.jpg", false, Constants::SPRITE_SHEET);
    //ResourceManager::LoadTexture2D("./res/textures/atlas_specular.png", true, Constants::SPRITE_SHEET_SPEC)->SetTypeSpecular();
    ResourceManager::SpriteSheet = { 128.0f, 128.0f, Constants::SPRITE_SHEET };
    //ResourceManager::SpriteSheet = { 500.0f, 500.0f, Constants::SPRITE_SHEET };
    Engine::Random::Init(111);
    Terrain::Vegetation::LSystemsManager::Init();

    Camera = std::make_shared<Renderer::Camera>(glm::vec3(0.0f, 30.0f, 0.0f));
    Renderer = std::make_unique<Renderer::SceneRenderer>(Camera.get());

    InitScene();
    Scene_.SetGlobalLight({ glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.7f) });
    InputHandler->Init(Camera.get());
    Renderer->Init();
}

void Game::ProcessInput(float delta) const {
    InputHandler->ProcessInput(delta);
}

void Game::Update([[maybe_unused]] float delta) {
    Scene_.Update();
}

void Game::Render() const {
    Renderer->Render(Scene_, Width(), Height());
    WindowManagerGl::EndFrame();
}

void Game::ExportScene() {
    // generate all chunks
    Scene_.Update(true);
    Engine::Files::Export::ExportScene(Scene_, "./export.json");
}

bool Game::Finished() const {
    return WindowManagerGl::ShouldCloseMainWindow();
}

unsigned Game::Width() const {
    return WindowManagerGl::Width;
}

unsigned Game::Height() const {
    return WindowManagerGl::Height;
}

void Game::InitScene() {
    Scene_.Init(Camera);
}
