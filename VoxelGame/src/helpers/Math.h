#pragma once
#include "glm/mat4x4.hpp"
#include <glm/vec3.hpp>

namespace Helpers {
namespace Math {
    namespace Detail {
        constexpr float EPSILON_F{ 0.001f };
    }

    void PackVecToMatrix(glm::mat4& m, glm::vec2 v);

    template<typename T>
    bool Equal(const T& a, const T& b) = delete;

    template<>
    bool Equal(const float& a, const float& b);
    int Mod(const float& x, int mod);
} // namespace Math

template<typename T>
struct CmpGlmVec {
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
