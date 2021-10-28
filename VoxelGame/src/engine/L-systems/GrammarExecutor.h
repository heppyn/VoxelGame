#pragma once
#include <stack>

#include "RandomGrammar.h"
#include "engine/GameObject.h"
#include "Turtle.h"

namespace LSystems {
class GrammarExecutor {
  public:
    float Yaw{ 90.0f };
    float Pitch{ 0.0f };

    GrammarExecutor() = default;
    explicit GrammarExecutor(float yaw, float pitch = 0.0f);

    [[nodiscard]] std::vector<GameObject> GenerateBasedOn(const glm::vec3& pos, const Detail::RandomGrammar& grammar, int numDerivations, unsigned salt);

  private:
    std::stack<Turtle> TStack_{};

    void ExecuteLetter(char letter, std::vector<GameObject>& objects, Turtle& turtle);
};
} // namespace LSystems
