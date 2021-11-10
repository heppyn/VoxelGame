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
    [[nodiscard]] std::vector<GameObject> GenerateBasedOn(const glm::vec3& pos, const LSystem& lSystem, float scale, int numDerivations, unsigned salt);

  private:
    int DerivationVar{ 0 };
    std::stack<Turtle> TStack_{};
    float Scale_{};

    void ExecuteLetter(char letter, const LSystem& lSystem, std::vector<GameObject>& objects, Turtle& turtle);
};
} // namespace LSystems
