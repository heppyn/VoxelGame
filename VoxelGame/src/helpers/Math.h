#pragma once
#include <vector>

#include "glm/mat4x4.hpp"
#include <glm/vec3.hpp>

namespace Helpers {
/**
 * \brief Provides useful mathematical operations
 */
namespace Math {
    namespace Detail {
        constexpr float EPSILON_F{ 0.001f };
    }

    void PackVecToMatrix(glm::mat4& m, glm::vec2 v);

    template<typename T>
    bool Equal(const T& a, const T& b) = delete;

    template<>
    bool Equal(const float& a, const float& b);

    template<>
    bool Equal(const glm::vec3& a, const glm::vec3& b);

    template<typename T>
    T ModT(const float& x, int mod) {
        return static_cast<T>(static_cast<int>(x) % mod);
    }

    int Mod(const float& x, int mod);

    template<typename T>
    [[nodiscard]] T Map(T x, T inMin, T inMax, T outMin, T outMax) {
        return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    }

    std::vector<glm::vec4> FrustumCornersWordSpace(const glm::mat4& proj, const glm::mat4& view);
    glm::vec3 FrustumCenter(const std::vector<glm::vec4>& corners);
    glm::mat4 OrthoLightSpace(const std::vector<glm::vec4>& corners, const glm::vec3& lightDir, float zMult);
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
