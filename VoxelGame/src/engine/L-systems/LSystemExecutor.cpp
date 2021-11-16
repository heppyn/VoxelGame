#include "LSystemExecutor.h"

#include "engine/GameObjectFactory.h"

LSystems::LSystemExecutor::LSystemExecutor(int derivationVar) : DerivationVar_(derivationVar) {}
LSystems::LSystemExecutor::LSystemExecutor(float randomAngle) : RandomAngle_(randomAngle) {}

std::vector<std::vector<GameObject>> LSystems::LSystemExecutor::GenerateBasedOn(const glm::vec3& pos, const LSystem& lSystem, float scale, int numDerivations, unsigned salt) {
    if (DerivationVar_) {
        numDerivations += static_cast<int>(Engine::Random::Get1dNoiseLimited(salt, DerivationVar_));
    }
    std::vector<std::vector<GameObject>> objects;
    objects.emplace_back();
    Scale_ = scale;
    LastMove_ = { 0.0f, 0.0f };
    // anchor the starting block to the bottom of the block
    Detail::Turtle turtle({ pos.x, pos.y - ((1.0f - scale) / 2.0f), pos.z }, scale);

    //std::cout << lSystem.Grammar.Derivate(numDerivations, salt) << "\n\n";

    for (const auto production = lSystem.Grammar.Derivate(numDerivations, salt); const auto letter : production) {
        ExecuteLetter(letter, lSystem, objects, turtle, salt);
        salt = Engine::Random::Get1dNoise(salt);
    }

    return objects;
}

void LSystems::LSystemExecutor::ExecuteLetter(char letter, const LSystem& lSystem, std::vector<std::vector<GameObject>>& objects, Detail::Turtle& turtle, unsigned salt) {
    // [-1.0, 1.0] * percentage
    const auto angleDelta = (Engine::Random::Get1dNoise0_1<float>(salt) - 0.5f) * 2.0f * RandomAngle_;
    // TODO: save this in hash map if it is too slow for large alphabet
    switch (letter) {
        case 'U':
            for (float x = 0.0f; x < Scale_; x += turtle.Scale()) {
                objects[turtle.OutputBuffer()].emplace_back(
                  GameObjectFactory::CreateObjectNoTex(turtle.Position(), turtle.Scale()));
                turtle.MoveUp();
            }
            LastMove_ = { 0.0f, turtle.Scale() };
            break;
        case 'F':
            for (float x = 0.0f; x < Scale_; x += turtle.Scale()) {
                objects[turtle.OutputBuffer()].emplace_back(
                  GameObjectFactory::CreateObjectNoTex(turtle.Position(), turtle.Scale()));
                turtle.MoveForward();
            }
            LastMove_ = { turtle.Scale(), 0.0f };
            break;
        case 'X': {
            const auto newScale = turtle.Scale() * lSystem.ShrinkRatio;
            const auto moveDiff = (turtle.Scale() - newScale) / 2.0f;
            // move in opposite direction of the previous move
            // objects would be separated by a gap, because the next object will be shrank
            // add all opposite moves
            if (LastMove_.x > 0.0f) {
                turtle.MoveBackward(moveDiff);
            }
            else if (LastMove_.y > 0.0f) {
                turtle.MoveDown(moveDiff);
            }
            turtle.Scale(newScale);
            break;
        }
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
        // character used for expanding grammar
        case 'E':
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
            assert(false && "Incomplete alphabet");
    }
}
