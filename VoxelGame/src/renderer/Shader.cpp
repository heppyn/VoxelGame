#include "Shader.h"

#include <iostream>
#include <glad/glad.h>

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

void Renderer::Shader::SetFloat(const char* name, float value, bool useShader) {
    if (useShader)
        Use();
    glUniform1f(glGetUniformLocation(Id, name), value);
}
void Renderer::Shader::SetInteger(const char* name, int value, bool useShader) {
    if (useShader)
        Use();
    glUniform1i(glGetUniformLocation(Id, name), value);
}
void Renderer::Shader::SetVector2f(const char* name, float x, float y, bool useShader) {
    if (useShader)
        Use();
    glUniform2f(glGetUniformLocation(Id, name), x, y);
}
void Renderer::Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader) {
    if (useShader)
        Use();
    glUniform2f(glGetUniformLocation(Id, name), value.x, value.y);
}
void Renderer::Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader) {
    if (useShader)
        Use();
    glUniform3f(glGetUniformLocation(Id, name), x, y, z);
}
void Renderer::Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader) {
    if (useShader)
        Use();
    glUniform3f(glGetUniformLocation(Id, name), value.x, value.y, value.z);
}
void Renderer::Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader) {
    if (useShader)
        Use();
    glUniform4f(glGetUniformLocation(Id, name), x, y, z, w);
}
void Renderer::Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader) {
    if (useShader)
        Use();
    glUniform4f(glGetUniformLocation(Id, name), value.x, value.y, value.z, value.w);
}
void Renderer::Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader) {
    if (useShader)
        Use();
    glUniformMatrix4fv(glGetUniformLocation(Id, name), 1, false, glm::value_ptr(matrix));
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