#include "LSystemExecutor.h"

#include <iostream>

#include "engine/GameObjectFactory.h"
#include "engine/Components/Transform.h"

LSystems::LSystemExecutor::LSystemExecutor(int derivationVar) : DerivationVar_(derivationVar) {}
LSystems::LSystemExecutor::LSystemExecutor(float randomAngle) : RandomAngle_(randomAngle) {
    assert(randomAngle >= 0.0f && randomAngle <= 1.0f);
}

LSystems::LSystemExecutor::LSystemExecutor(int derivationVar, float randomAngle)
  : DerivationVar_(derivationVar), RandomAngle_(randomAngle) {
    assert(randomAngle >= 0.0f && randomAngle <= 1.0f);
}

std::vector<std::vector<GameObject>> LSystems::LSystemExecutor::GenerateBasedOn(const glm::vec3& pos, const LSystem& lSystem, float minScale, int numDerivations, unsigned salt, bool optimize /* = false*/) {
    if (DerivationVar_) {
        const auto derVar = static_cast<int>(Engine::Random::Get1dNoiseLimited(salt, DerivationVar_));
        numDerivations += derVar;
        Scale_ = minScale + static_cast<float>(derVar) * ScaleFactor_;
    }
    else {
        Scale_ = minScale;
    }
    std::vector<std::vector<GameObject>> objects;
    objects.emplace_back();
    LastMove_ = { 0.0f, 0.0f };
    // anchor the starting block to the bottom of the block
    Detail::Turtle turtle({ pos.x, pos.y - ((1.0f - Scale_) / 2.0f), pos.z }, Scale_);

    //std::cout << lSystem.Grammar.Derivate(numDerivations, salt) << "\n\n";

    for (const auto production = lSystem.Grammar.Derivate(numDerivations, salt); const auto letter : production) {
        ExecuteLetter(letter, lSystem, objects, turtle, salt);
        salt = Engine::Random::Get1dNoise(salt);
    }

    if (optimize) {
        return OptimizeModel(std::move(objects));
    }

    return objects;
}

void LSystems::LSystemExecutor::ScaleDerivations(int derivationVar, float minScale, float maxScale) {
    assert(minScale <= maxScale);
    assert(derivationVar >= 1);

    DerivationVar_ = derivationVar;
    // derivation variance comes from [0, derivationVar - 1]
    ScaleFactor_ = (maxScale - minScale) / static_cast<float>(derivationVar - 1);
}

void LSystems::LSystemExecutor::ExecuteLetter(char letter, const LSystem& lSystem, std::vector<std::vector<GameObject>>& objects, Detail::Turtle& turtle, unsigned salt) {
    // [-1.0, 1.0] * percentage
    const auto angleDelta = (Engine::Random::Get1dNoise0_1<float>(salt) - 0.5f) * 2.0f * RandomAngle_;
    auto first = true;
    // TODO: save this in hash map if it is too slow for large alphabet
    switch (letter) {
        // same as U, but allows more diverse grammar rules
        case 'u':
        case 'U':
            // always place at least one block
            for (float x = turtle.Scale(); x <= Scale_ || first; x += turtle.Scale()) {
                objects[turtle.OutputBuffer()].emplace_back(
                  GameObjectFactory::CreateObjectNoTex(turtle.Position(), turtle.Scale()));
                turtle.MoveUp();
                first = false;
            }
            LastMove_ = { 0.0f, turtle.Scale() };
            break;
        // same as F, but allows more diverse grammar rules
        case 'f':
        case 'F':
            // always place at least one block
            for (float x = turtle.Scale(); x <= Scale_ || first; x += turtle.Scale()) {
                objects[turtle.OutputBuffer()].emplace_back(
                  GameObjectFactory::CreateObjectNoTex(turtle.Position(), turtle.Scale()));
                turtle.MoveForward();
                first = false;
            }
            LastMove_ = { turtle.Scale(), 0.0f };
            break;
        // shrink turtle
        case 'x':
            UpdateTurtleScale(turtle, turtle.Scale() * lSystem.ShrinkRatio);
            break;
        // enlarge turtle
        case 'X':
            UpdateTurtleScale(turtle, turtle.Scale() / lSystem.ShrinkRatio);
            break;
        // scale back to the original scale
        case 'S':
            UpdateTurtleScale(turtle, Scale_);
            break;
        // using right hand system, keep + to match the book
        case '+':
            turtle.Rotate(-lSystem.Yaw + angleDelta * lSystem.Yaw, 0.0f);
            break;
        case '-':
            turtle.Rotate(lSystem.Yaw + angleDelta * lSystem.Yaw, 0.0f);
            break;
        case '&':
            turtle.Rotate(0.0f, -lSystem.Pitch + angleDelta * lSystem.Pitch);
            break;
        case '^':
            turtle.Rotate(0.0f, lSystem.Pitch + angleDelta * lSystem.Pitch);
            break;
        case '[':
            TStack_.emplace(turtle);
            break;
        case ']':
            turtle = TStack_.top();
            TStack_.pop();
            break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            const uint8_t buffer = letter - '0';
            while (objects.size() <= buffer) {
                objects.emplace_back();
            }
            turtle.OutputBuffer(buffer);
            break;
        }

        default:
            // Symbol used for intermediate production
            break;
    }
}

void LSystems::LSystemExecutor::UpdateTurtleScale(Detail::Turtle& turtle, float newScale) const {
    const auto moveDiff = (turtle.Scale() - newScale) / 2.0f;
    // move in opposite direction of the previous move if scale is positive
    // objects would be separated by a gap, because the next object will be shrank
    // add all opposite moves
    if (LastMove_.x > 0.0f) {
        turtle.MoveBackward(moveDiff);
    }
    else if (LastMove_.y > 0.0f) {
        turtle.MoveDown(moveDiff);
    }
    turtle.Scale(newScale);
}

std::vector<std::vector<GameObject>> LSystems::LSystemExecutor::OptimizeModel(std::vector<std::vector<GameObject>>&& model) const {
    // optimization for use case where leaves are in buffer 1 and are bigger than branches
    if (model.size() < 2) {
        return std::move(model);
    }
    auto endIt = model[0].end();
    for (const auto& object : model[1]) {
        assert(object.HasComponent<Components::Transform>());
        const auto& trans = object.GetComponent<Components::Transform>();
        auto it = model[0].begin();

        while (it < endIt) {
            if (trans.IsOtherInside(*it)) {
                std::iter_swap(it, (endIt - 1));
                // last objects will be discarded
                --endIt;
                // check current object again - don't move iterator
            }
            else {
                ++it;
            }
        }
    }

    model[0].erase(endIt, model[0].end());
    return std::move(model);
}
