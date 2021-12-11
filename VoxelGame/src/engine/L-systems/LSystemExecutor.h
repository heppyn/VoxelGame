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
    explicit LSystemExecutor(int derivationVar, float randomAngle);
    [[nodiscard]] std::vector<std::vector<GameObject>> GenerateBasedOn(const glm::vec3& pos, const LSystem& lSystem, float minScale, int numDerivations, unsigned salt, bool optimize = false);
    void ScaleDerivations(int derivationVar, float minScale, float maxScale);

  private:
    int DerivationVar_{ 0 };
    float ScaleFactor_{ 0.0f };
    // variation of L-system angle
    // percentage of angle change [0.0, 1.0]
    float RandomAngle_{ 0.2f };

    std::stack<Detail::Turtle> TStack_{};
    float Scale_{};
    glm::vec2 LastMove_{ 0.0f };

    void ExecuteLetter(char letter, const LSystem& lSystem, std::vector<std::vector<GameObject>>& objects, Detail::Turtle& turtle, unsigned salt);
    void UpdateTurtleScale(Detail::Turtle& turtle, float newScale) const;
    [[nodiscard]] std::vector<std::vector<GameObject>> OptimizeModel(std::vector<std::vector<GameObject>>&& model) const;

};
} // namespace LSystems
