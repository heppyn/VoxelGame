#pragma once

#include <string>
#include <vector>
#include <utility>

#include <glm/glm.hpp>


namespace Renderer {
class Shader {
  private:
    using Macros_t = std::vector<std::pair<std::string, std::string>>;

  public:
    // state
    unsigned int Id{ 0 };
    // sets the current shader as active
    Shader& Use();
    // compiles the shader from given source code
    void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);
    // compiles the shader from given source code
    // and redefines macros eg. #define LEVELS 3
    void CompileWithMacros(std::string&& vertexSource, std::string&& fragmentSource, std::string&& geometrySource, const Macros_t& macros);
    void Delete();
    // utility functions
    void SetFloat(const char* name, float value, bool useShader = false);
    void SetInteger(const char* name, int value, bool useShader = false);
    void SetVector2f(const char* name, float x, float y, bool useShader = false);
    void SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);
    void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
    void SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);
    void SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
    void SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);
    void SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);

  private:
    // checks if compilation or linking failed and if so, print the error logs
    static void CheckCompileErrors(unsigned int object, const std::string& type);

    // used for testing purposes
  protected:
    static bool ReplaceMacros(std::string& source, const Macros_t& macros);
};
} // namespace Renderer
