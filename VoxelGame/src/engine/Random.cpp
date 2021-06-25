#include "Random.h"

siv::BasicPerlinNoise<float> Engine::Random::Perlin{};
unsigned Engine::Random::Seed{ 0 };
std::random_device Engine::Random::RandomGen{};

void Engine::Random::Init() {
    Init(RandomGen());
}

void Engine::Random::Init(unsigned seed) {
    Seed = seed;
    Perlin.reseed(Seed);
}
