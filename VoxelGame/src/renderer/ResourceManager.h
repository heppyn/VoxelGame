#pragma once

#include <map>
#include <string>
#include <memory>

#include "Shader.h"
#include "Texture2D.h"

class ResourceManager {
  public:
    static std::map<std::string, std::unique_ptr<Shader>> Shaders;
    static std::map<std::string, std::unique_ptr<Texture2D>> Textures;

    static Shader* LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name);
    static Shader* GetShader(std::string& name);
    static Shader* GetShader(const char* name);

    static Texture2D* LoadTexture2D(const char* file, bool alpha, const std::string& name);
    static Texture2D* GetTexture2D(std::string& name);
    static Texture2D* GetTexture2D(const char* name);

    static void Clear();

  private:
    ResourceManager() = default; // resource manager is a singleton
    static Shader* LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    static Texture2D* LoadTexture2DFromFile(const char* file, bool alpha);
};
