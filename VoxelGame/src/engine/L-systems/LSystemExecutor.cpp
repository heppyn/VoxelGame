#include "LSystemExecutor.h"

#include <iostream>

#include "engine/GameObjectFactory.h"


std::vector<GameObject> LSystems::LSystemExecutor::GenerateBasedOn(const glm::vec3& pos, const LSystem& lSystem, int numDerivations, unsigned salt) {
    std::vector<GameObject> objects;
    Turtle turtle(pos, 1.0f);

    std::cout << lSystem.Grammar.Derivate(numDerivations, salt) << "\n\n";

    for (const auto production = lSystem.Grammar.Derivate(numDerivations, salt); const auto letter : production) {
        ExecuteLetter(letter, lSystem, objects, turtle);
    }

    return objects;
}

void LSystems::LSystemExecutor::ExecuteLetter(char letter, const LSystem& lSystem, std::vector<GameObject>& objects, Turtle& turtle) {
    // TODO: save this in hash map if it is too slow for large alphabet
    switch (letter) {
        case 'U':
            // TODO: use factory for creating objects
            for (float x = 0.0f; x < 1.0f; x += turtle.Scale()) {
                objects.emplace_back(GameObjectFactory::CreateObject(turtle.Position(), { 4.0f, 3.0f }, turtle.Scale()));
                turtle.MoveUp();
            }
            break;
        case 'F':
            // TODO: use factory for creating objects
            for (float x = 0.0f; x < 1.0f; x += turtle.Scale()) {
                objects.emplace_back(GameObjectFactory::CreateObject(turtle.Position(), { 4.0f, 3.0f }, turtle.Scale()));
                turtle.MoveForward();
            }
            break;
        case 'X':
            turtle.Scale(turtle.Scale() * lSystem.ShrinkRatio);
            break;
        // using right hand system, keep + to match the book
        case '+':
            turtle.Rotate(-lSystem.Yaw, 0.0f);
            break;
        case '-':
            turtle.Rotate(lSystem.Yaw, 0.0f);
            break;
        case '&':
            turtle.Rotate(0.0f, -lSystem.Pitch);
            break;
        case '^':
            turtle.Rotate(0.0f, lSystem.Pitch);
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