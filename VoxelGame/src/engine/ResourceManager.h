#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <utility>

#include "renderer/Shader.h"
#include "renderer/Texture2D.h"
#include "renderer/SpriteSheet.h"

class ResourceManager {
  private:
    using ShaderMacros_t = std::vector<std::pair<std::string, std::string>>;

  public:
    static std::map<std::string, std::unique_ptr<Renderer::Shader>> Shaders;
    static std::map<std::string, std::unique_ptr<Renderer::Texture2D>> Textures;
    static Renderer::SpriteSheet SpriteSheet;

    static Renderer::Shader* LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name);
    static Renderer::Shader* SetShaderMacros(const std::string& name, const ShaderMacros_t& macros);
    static Renderer::Shader* GetShader(const std::string& name);
    static Renderer::Shader* GetShader(const char* name);

    static Renderer::Texture2D* LoadTexture2D(const char* file, bool alpha, const std::string& name);
    static Renderer::Texture2D* LoadTexture2D(const std::string& file, bool alpha, const std::string& name);
    static Renderer::Texture2D* GetTexture2D(std::string& name);
    static Renderer::Texture2D* GetTexture2D(const char* name);

    static glm::vec2 GetSpriteSheetSize();

    static void Clear();

  private:
    ResourceManager() = default; // resource manager is a singleton
    static std::unique_ptr<Renderer::Shader> LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);
    static std::unique_ptr<Renderer::Shader> LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const ShaderMacros_t& macros);
    static std::string LoadShaderCodeFromFile(const char* shaderFile);

    static Renderer::Texture2D* LoadTexture2DFromFile(const char* file, bool alpha);

    static std::map<std::string, std::array<const char*, 3>> ShaderSources_;
};
