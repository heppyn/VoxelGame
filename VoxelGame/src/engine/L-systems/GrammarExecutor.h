#pragma once
#include "RandomGrammar.h"
#include "engine/GameObject.h"
#include "Turtle.h"

namespace LSystems {
class GrammarExecutor {
public:
    [[nodiscard]] std::vector<GameObject> GenerateBasedOn(const Detail::RandomGrammar& grammar, int numDerivations, unsigned salt) const;

private:
    void ExecuteLetter(char letter, std::vector<GameObject>& objects, Turtle& turtle) const;
};
} // namespace LSystems
