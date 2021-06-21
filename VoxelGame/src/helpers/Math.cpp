#include "Math.h"

void Helpers::Math::PackVecToMatrix(glm::mat4& m, glm::vec2 v)
{
    m[0].w = v.x;
    m[1].w = v.y;
}
