#include "LSystemExecutor.h"

#include "engine/GameObjectFactory.h"

LSystems::LSystemExecutor::LSystemExecutor(int derivationVar) : DerivationVar_(derivationVar) {}
LSystems::LSystemExecutor::LSystemExecutor(float randomAngle) : RandomAngle_(randomAngle) {}

std::vector<GameObject> LSystems::LSystemExecutor::GenerateBasedOn(const glm::vec3& pos, const LSystem& lSystem, float scale, int numDerivations, unsigned salt) {
    if (DerivationVar_) {
        numDerivations += static_cast<int>(Engine::Random::Get1dNoiseLimited(salt, DerivationVar_));
    }
    std::vector<GameObject> objects;
    Scale_ = scale;
    // anchor the starting block to the bottom of the block
    Detail::Turtle turtle({ pos.x, pos.y - ((1.0f - scale) / 2.0f), pos.z }, scale);

    //std::cout << lSystem.Grammar.Derivate(numDerivations, salt) << "\n\n";

    for (const auto production = lSystem.Grammar.Derivate(numDerivations, salt); const auto letter : production) {
        ExecuteLetter(letter, lSystem, objects, turtle, salt);
        salt = Engine::Random::Get1dNoise(salt);
    }

    return objects;
}

void LSystems::LSystemExecutor::ExecuteLetter(char letter, const LSystem& lSystem, std::vector<GameObject>& objects, Detail::Turtle& turtle, unsigned salt) {
    // [-1.0, 1.0] * percentage
    const auto angleDelta = (Engine::Random::Get1dNoise0_1<float>(salt) - 0.5f) * 2.0f * RandomAngle_;
    // TODO: save this in hash map if it is too slow for large alphabet
    switch (letter) {
        case 'U':
            for (float x = 0.0f; x < Scale_; x += turtle.Scale()) {
                objects.emplace_back(GameObjectFactory::CreateObjectNoTex(turtle.Position(), turtle.Scale()));
                turtle.MoveUp();
            }
            break;
        case 'F':
            for (float x = 0.0f; x < Scale_; x += turtle.Scale()) {
                objects.emplace_back(GameObjectFactory::CreateObjectNoTex(turtle.Position(), turtle.Scale()));
                turtle.MoveForward();
            }
            break;
        case 'X':
            turtle.Scale(turtle.Scale() * lSystem.ShrinkRatio);
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
        // character used for expanding grammar
        case 'E':
            break;

        default:
            assert(false && "Incomplete alphabet");
    }
}
