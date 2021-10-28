#include "GrammarExecutor.h"

#include <iostream>

LSystems::GrammarExecutor::GrammarExecutor(float yaw, float pitch)
  : Yaw(yaw), Pitch(pitch) {}

std::vector<GameObject> LSystems::GrammarExecutor::GenerateBasedOn(const glm::vec3& pos, const Detail::RandomGrammar& grammar, int numDerivations, unsigned salt) {
    std::vector<GameObject> objects;
    // for testing purposes start from 0 0 0
    Turtle turtle(pos);

    std::cout << grammar.Derivate(numDerivations, salt) << "\n\n";

    for (const auto production = grammar.Derivate(numDerivations, salt); const auto letter : production) {
        ExecuteLetter(letter, objects, turtle);
    }

    return objects;
}

void LSystems::GrammarExecutor::ExecuteLetter(char letter, std::vector<GameObject>& objects, Turtle& turtle) {
    // TODO: save this in hash map if it is too slow for large alphabet
    switch (letter) {
        case 'U':
            // TODO: use factory for creating objects
            objects.emplace_back(turtle.Position(), glm::vec2(0.0f));
            turtle.MoveUp(1.0f);
            break;
        case 'F':
            // TODO: use factory for creating objects
            objects.emplace_back(turtle.Position(), glm::vec2(0.0f));
            turtle.MoveForward(1.0f);
            break;
        // using right hand system, keep + to match the book
        case '+':
            turtle.Rotate(-Yaw, 0.0f);
            break;
        case '-':
            turtle.Rotate(Yaw, 0.0f);
            break;
        case '&':
            turtle.Rotate(0.0f, -Pitch);
            break;
        case '^':
            turtle.Rotate(0.0f, Pitch);
            break;
        case '[':
            TStack_.emplace(turtle);
            break;
        case ']':
            turtle = TStack_.top();
            TStack_.pop();
            break;

        default:
            assert(false, "Incomplete alphabet");
    }
}
