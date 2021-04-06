#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) \
    if (!(x))     \
        __debugbreak()

#define GL_CALL(x)   \
    GlClearError(); \
    x;              \
    ASSERT(GlLogCall(#x, __FILE__, __LINE__))

void GlClearError();
bool GlLogCall(const char* function, const char* file, int line);
void APIENTRY GlDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);