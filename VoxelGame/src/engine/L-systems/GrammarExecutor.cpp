#include "GrammarExecutor.h"
std::vector<GameObject> LSystems::GrammarExecutor::GenerateBasedOn(const Detail::RandomGrammar& grammar, int numDerivations, unsigned salt) const {
    std::vector<GameObject> objects;
    // for testing purposes start from 0 0 0
    Turtle turtle(glm::vec3(0.0f));

    for (const auto production = grammar.Derivate(numDerivations, salt); const auto letter : production) {
        ExecuteLetter(letter, objects, turtle);
    }

    return objects;
}

void LSystems::GrammarExecutor::ExecuteLetter(char letter, std::vector<GameObject>& objects, Turtle& turtle) const {
    // TODO: save this in hash map if it is too slow for large alphabet
    switch (letter) {
        case 'F':
            // TODO: use factory for creating objects
            objects.emplace_back(turtle.Position(), glm::vec2(0.0f));
            turtle.MoveForward(1.0f);
            break;
        // using right hand system, keep + to match the book
        case '+':
            turtle.Rotate(-90.0f, 0.0f);
            break;
        case '-':
            turtle.Rotate(90.0f, 0.0f);
            break;
        default:
            assert(false, "Incomplete alphabet");
    }
}
