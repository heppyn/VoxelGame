#include "Math.h"

void Helpers::Math::PackVecToMatrix(glm::mat4& m, glm::vec2 v)
{
    m[0].w = v.x;
    m[1].w = v.y;
}

int Helpers::Math::Mod(const float& x, int mod)
{
    return ModT<int>(x, mod);
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
bool Helpers::Math::Equal<float>(const float& a, const float& b)
{
    return std::abs(a - b) < Math::Detail::EPSILON_F;
}
