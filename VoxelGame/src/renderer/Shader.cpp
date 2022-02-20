#include "Shader.h"

#include <iostream>
#include <sstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Renderer::Shader& Renderer::Shader::Use() {
    glUseProgram(Id);
    return *this;
}

void Renderer::Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
    unsigned int sVertex, sFragment, gShader = 0;
    // vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    CheckCompileErrors(sVertex, "VERTEX");
    // fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    CheckCompileErrors(sFragment, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr) {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        CheckCompileErrors(gShader, "GEOMETRY");
    }
    // shader program
    Id = glCreateProgram();
    glAttachShader(Id, sVertex);
    glAttachShader(Id, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(Id, gShader);
    glLinkProgram(Id);
    CheckCompileErrors(Id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void Renderer::Shader::CompileWithMacros(std::string&& vertexSource, std::string&& fragmentSource, std::string&& geometrySource, const Macros_t& macros) {
    auto foundMacro = false;
    foundMacro |= ReplaceMacros(vertexSource, macros);
    foundMacro |= ReplaceMacros(fragmentSource, macros);
    foundMacro |= ReplaceMacros(geometrySource, macros);

    if (!foundMacro) {
        std::cout << "WARNING::SHADER marco not found in shader\n";
    }

    Compile(vertexSource.c_str(), fragmentSource.c_str(), geometrySource.empty() ? nullptr : geometrySource.c_str());
}

void Renderer::Shader::SetFloat(const char* name, float value, bool useShader) {
    // when writing new code, use glProgramUniform to set uniforms directly
    // into programs without having to bind or use the program. Only use
    // the following mechanism if you absolutely must remain backwards compatible
    // with some functions that set uniforms on a program that is bound to the context.
    // don't use glUniform1f
    if (useShader)
        Use();
    glProgramUniform1f(Id, glGetUniformLocation(Id, name), value);
}
void Renderer::Shader::SetInteger(const char* name, int value, bool useShader) {
    if (useShader)
        Use();
    glProgramUniform1i(Id, glGetUniformLocation(Id, name), value);
}
void Renderer::Shader::SetVector2f(const char* name, float x, float y, bool useShader) {
    if (useShader)
        Use();
    glProgramUniform2f(Id, glGetUniformLocation(Id, name), x, y);
}
void Renderer::Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader) {
    if (useShader)
        Use();
    glProgramUniform2f(Id, glGetUniformLocation(Id, name), value.x, value.y);
}
void Renderer::Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader) {
    if (useShader)
        Use();
    glProgramUniform3f(Id, glGetUniformLocation(Id, name), x, y, z);
}
void Renderer::Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader) {
    if (useShader)
        Use();
    glProgramUniform3f(Id, glGetUniformLocation(Id, name), value.x, value.y, value.z);
}
void Renderer::Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader) {
    if (useShader)
        Use();
    glProgramUniform4f(Id, glGetUniformLocation(Id, name), x, y, z, w);
}
void Renderer::Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader) {
    if (useShader)
        Use();
    glProgramUniform4f(Id, glGetUniformLocation(Id, name), value.x, value.y, value.z, value.w);
}
void Renderer::Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader) {
    if (useShader)
        Use();
    glProgramUniformMatrix4fv(Id, glGetUniformLocation(Id, name), 1, false, glm::value_ptr(matrix));
}


void Renderer::Shader::CheckCompileErrors(unsigned int object, const std::string& type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
    else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
}

bool Renderer::Shader::ReplaceMacros(std::string& source, const Macros_t& macros) {
    // Look for #define CONSTANT name
    std::istringstream in(source);
    std::ostringstream out;
    auto foundSome = false;

    for (std::string line; std::getline(in, line, '\n');) {
        auto found = false;
        if (line.starts_with("#define ")) {
            for (const auto& [name, value] : macros) {
                if (line.starts_with("#define " + name + ' ')) {
                    foundSome = true;
                    found = true;

                    out << "#define " << name << ' ' << value << '\n';
                }
            }
        }
        if (!found) {
            out << line << '\n';
        }
    }

    if (!foundSome)
        return false;

    source = out.str();
    return true;
}
