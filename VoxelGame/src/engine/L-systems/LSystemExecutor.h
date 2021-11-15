#pragma once
#include <stack>

#include "LSystem.h"
#include "engine/GameObject.h"
#include "Turtle.h"

namespace LSystems {
class LSystemExecutor {
  public:
    LSystemExecutor() = default;
    explicit LSystemExecutor(int derivationVar);
    explicit LSystemExecutor(float randomAngle);
    [[nodiscard]] std::vector<GameObject> GenerateBasedOn(const glm::vec3& pos, const LSystem& lSystem, float scale, int numDerivations, unsigned salt);

  private:
    int DerivationVar_{ 0 };
    // variation of L-system angle
    // percentage of angle change [0.0, 1.0]
    float RandomAngle_{ 0.2f };

    std::stack<Detail::Turtle> TStack_{};
    float Scale_{};
    glm::vec2 LastMove_{ 0.0f };

    void ExecuteLetter(char letter, const LSystem& lSystem, std::vector<GameObject>& objects, Detail::Turtle& turtle, unsigned salt);
};
} // namespace LSystems
