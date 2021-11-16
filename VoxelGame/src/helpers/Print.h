#pragma once
#include <iostream>
#include <sstream>

#include "glm/mat4x4.hpp"

namespace Helpers {
inline void PrintMat4(const glm::mat4& mat) {
    std::cout << mat[0].x << ' ' << mat[0].y << ' ' << mat[0].z << ' ' << mat[0].w << '\n';
    std::cout << mat[1].x << ' ' << mat[1].y << ' ' << mat[1].z << ' ' << mat[1].w << '\n';
    std::cout << mat[2].x << ' ' << mat[2].y << ' ' << mat[2].z << ' ' << mat[2].w << '\n';
    std::cout << mat[3].x << ' ' << mat[3].y << ' ' << mat[3].z << ' ' << mat[3].w << '\n';
}

inline void Print(const glm::vec4& vec) {
    std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << ' ' << vec.w << '\n';
}

inline std::string ToString(const glm::vec3& vec) {
    std::stringstream ss;
    ss << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
    return ss.str();
}
} // namespace Helpers
