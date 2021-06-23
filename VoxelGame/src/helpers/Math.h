#pragma once
#include "glm/mat4x4.hpp"
#include <glm/vec3.hpp>

namespace Helpers {
namespace Math {

    void PackVecToMatrix(glm::mat4& m, glm::vec2 v);
}

template<typename T>
struct CmpGlmVec
{
    constexpr bool operator()(const T& lhs, const T& rhs) const = delete;
};

template<>
struct CmpGlmVec<glm::vec3> {
    bool operator()(const glm::vec3& lhs, const glm::vec3& rhs) const;
};

template<>
struct CmpGlmVec<glm::vec2> {
    bool operator()(const glm::vec2& lhs, const glm::vec2& rhs) const;
};
} // namespace Helpers
