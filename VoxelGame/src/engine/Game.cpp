#include "Game.h"

#include "ResourceManager.h"
#include "../open_gl/WindowManagerGl.h"
#include "../helpers/Constants.h"
#include "Random.h"
#include "engine/files/Export.h"
#include "Log.h"


Game::Game() {
    // init main engine systems
    Engine::Log::Init();
}

Game::~Game() {
    ResourceManager::Clear();
}

void Game::Init() {
    ResourceManager::LoadShader("./res/shaders/LightBatch.vert", "./res/shaders/Light.frag", nullptr, "lightBatch");
    ResourceManager::LoadShader("./res/shaders/Mesh.vert", "./res/shaders/Mesh.frag", nullptr, "meshShader");
    ResourceManager::LoadShader("./res/shaders/Shadow.vert", "./res/shaders/Shadow.frag", nullptr, "shadow");
    ResourceManager::LoadShader(
      "./res/shaders/Shadow_csm.vert", "./res/shaders/Shadow.frag", "./res/shaders/Shadow_csm.geom", "shadow_csm");
    ResourceManager::LoadShader(
      "./res/shaders/Shadow_csm_closed.vert", "./res/shaders/Empty.frag", "./res/shaders/Shadow_csm_closed.geom", "shadow_csm_closed");
    ResourceManager::LoadShader(
      "./res/shaders/Light_csm.vert", "./res/shaders/Light_csm.frag", nullptr, "light_csm");

    ResourceManager::LoadTexture2D("./res/textures/white.png", true, "white");
    ResourceManager::LoadTexture2D(Constants::VOXEL_PACK_PATH_SH + "sprite_sheet.png", true, Constants::SPRITE_SHEET);
    ResourceManager::LoadTexture2D(Constants::VOXEL_PACK_PATH_SH + "sprite_sheet.png", true, Constants::SPRITE_SHEET_SPEC)->SetTypeSpecular();
    // ResourceManager::LoadTexture2D("./res/textures/atlas.jpg", false, Constants::SPRITE_SHEET);
    // ResourceManager::LoadTexture2D("./res/textures/atlas_specular.png", true, Constants::SPRITE_SHEET_SPEC)->SetTypeSpecular();
    ResourceManager::SpriteSheet = { 128.0f, 128.0f, Constants::SPRITE_SHEET };
    // ResourceManager::SpriteSheet = { 500.0f, 500.0f, Constants::SPRITE_SHEET };
    Engine::Random::Init(111);

    Camera = std::make_shared<Renderer::Camera>(glm::vec3(0.0f, 15.0f, 0.0f));
    Renderer = std::make_unique<Renderer::SceneRenderer>(Camera.get());

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
    Renderer->Render(Scene_, WindowManagerGl::Width, WindowManagerGl::Height);
    WindowManagerGl::EndFrame();
}

void Game::ExportScene() {
    // generate all chunks
    Scene_.Update(true);
    Engine::Files::Export::ExportScene(Scene_, "./export.json");
}

bool Game::IsRunning() const {
    return !WindowManagerGl::ShouldCloseMainWindow();
}

void Game::InitScene() {
    Scene_.Init(Camera);
}
