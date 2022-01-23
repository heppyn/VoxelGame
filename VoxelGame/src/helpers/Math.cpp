#include "Math.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

void Helpers::Math::PackVecToMatrix(glm::mat4& m, glm::vec2 v) {
    m[0].w = v.x;
    m[1].w = v.y;
}

template<>
bool Helpers::Math::Equal<glm::vec<3, float, glm::defaultp>>(const glm::vec3& a, const glm::vec3& b) {
    return Equal(a.x, b.x) && Equal(a.y, b.y) && Equal(a.z, b.z);
}

int Helpers::Math::Mod(const float& x, int mod) {
    return ModT<int>(x, mod);
}

std::vector<glm::vec4> Helpers::Math::FrustumCornersWordSpace(const glm::mat4& proj, const glm::mat4& view) {
    const auto inv = glm::inverse(proj * view);

    std::vector<glm::vec4> frustumCorners;
    for (unsigned int x = 0; x < 2; ++x) {
        for (unsigned int y = 0; y < 2; ++y) {
            for (unsigned int z = 0; z < 2; ++z) {
                const glm::vec4 pt =
                  inv * glm::vec4(2.0f * x - 1.0f, 2.0f * y - 1.0f, 2.0f * z - 1.0f, 1.0f);
                frustumCorners.emplace_back(pt / pt.w);
            }
        }
    }

    return frustumCorners;
}

glm::vec3 Helpers::Math::FrustumCenter(const std::vector<glm::vec4>& corners) {
    auto center = glm::vec3(0.0f);
    for (const auto& v : corners) {
        center += glm::vec3(v);
    }
    center /= corners.size();

    return center;
}

glm::mat4 Helpers::Math::OrthoLightSpace(const std::vector<glm::vec4>& corners, const glm::vec3& lightDir, const float zMult) {
    const auto center = FrustumCenter(corners);
    const auto lightView = glm::lookAt(
      center,
      center + lightDir,
      glm::vec3(0.0f, 1.0f, 0.0f));

    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::min();
    float minZ = std::numeric_limits<float>::max();
    float maxZ = std::numeric_limits<float>::min();
    for (const auto& v : corners) {
        const auto trf = lightView * v;
        minX = std::min(minX, trf.x);
        maxX = std::max(maxX, trf.x);
        minY = std::min(minY, trf.y);
        maxY = std::max(maxY, trf.y);
        minZ = std::min(minZ, trf.z);
        maxZ = std::max(maxZ, trf.z);
    }

    // move the near and far plane to include invisible geometry
    if (minZ < 0) {
        minZ *= zMult;
    }
    else {
        minZ /= zMult;
    }
    if (maxZ < 0) {
        maxZ /= zMult;
    }
    else {
        maxZ *= zMult;
    }

    const glm::mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ);

    return lightProjection * lightView;
}

bool Helpers::CmpGlmVec<glm::vec<3, float, glm::defaultp>>::operator()(const glm::vec3& lhs, const glm::vec3& rhs) const {
    return lhs.x < rhs.x
           || lhs.x <= rhs.x && lhs.y < rhs.y
           || lhs.x <= rhs.x && lhs.y <= rhs.y && lhs.z < rhs.z;
}

bool Helpers::CmpGlmVec<glm::vec<2, float, glm::defaultp>>::operator()(const glm::vec2& lhs, const glm::vec2& rhs) const {
    return lhs.x < rhs.x
           || lhs.x <= rhs.x && lhs.y < rhs.y;
}

template<>
bool Helpers::Math::Equal<float>(const float& a, const float& b) {
    return std::abs(a - b) < Math::Detail::EPSILON_F;
}
