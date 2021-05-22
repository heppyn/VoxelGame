#pragma once

#include <map>
#include <string>
#include <memory>

#include "renderer/Shader.h"
#include "renderer/Texture2D.h"

class ResourceManager {
  public:
    static std::map<std::string, std::unique_ptr<Renderer::Shader>> Shaders;
    static std::map<std::string, std::unique_ptr<Renderer::Texture2D>> Textures;

    static Renderer::Shader* LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name);
    static Renderer::Shader* GetShader(std::string& name);
    static Renderer::Shader* GetShader(const char* name);

    static Renderer::Texture2D* LoadTexture2D(const char* file, bool alpha, const std::string& name);
    static Renderer::Texture2D* GetTexture2D(std::string& name);
    static Renderer::Texture2D* GetTexture2D(const char* name);

    static glm::vec2 GetSpriteSheetSize();

    static void Clear();

  private:
    ResourceManager() = default; // resource manager is a singleton
    static Renderer::Shader* LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    static Renderer::Texture2D* LoadTexture2DFromFile(const char* file, bool alpha);
};
