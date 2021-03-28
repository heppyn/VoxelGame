#pragma once

#include <map>
#include <string>

#include <glad/glad.h>

#include "Shader.h"
#include "Texture2D.h"

class ResourceManager {
  public:
    static std::map<std::string, Shader> m_shaders;
    static std::map<std::string, Texture2D> m_textures;

    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name);
    static Shader GetShader(std::string& name);

    static Texture2D LoadTexture2D(const char* file, bool alpha, const std::string& name);
    static Texture2D GetTexture2D(std::string& name);

    static void Clear();

  private:
    ResourceManager() = default; // resource manager is a singleton
    static Shader LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    static Texture2D LoadTexture2DFromFile(const char* file, bool alpha);
};
