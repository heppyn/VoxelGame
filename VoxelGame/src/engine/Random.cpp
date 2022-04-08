#include "Random.h"

#include "helpers/Math.h"

siv::BasicPerlinNoise<float> Engine::Random::Perlin{};
SimplexNoise Engine::Random::Simplex{};
unsigned Engine::Random::Seed{ 0 };
std::random_device Engine::Random::RandomGen{};

void Engine::Random::Init() {
    Init(RandomGen());
}

void Engine::Random::Init(unsigned seed) {
    Seed = seed;
    Perlin.reseed(Seed);
    Simplex = SimplexNoise(seed);
}

bool Engine::Random::IsLocalMaxPerlin(const glm::vec2& pos, float freq, int octaves) {
    const auto r = Perlin.accumulatedOctaveNoise2D_0_1(pos.x / freq, pos.y / freq, octaves);
    const auto r1 = Perlin.accumulatedOctaveNoise2D_0_1((pos.x + 1) / freq, pos.y / freq, octaves);
    const auto r2 = Perlin.accumulatedOctaveNoise2D_0_1((pos.x - 1) / freq, pos.y / freq, octaves);
    const auto r3 = Perlin.accumulatedOctaveNoise2D_0_1(pos.x / freq, (pos.y + 1) / freq, octaves);
    const auto r4 = Perlin.accumulatedOctaveNoise2D_0_1(pos.x / freq, (pos.y - 1) / freq, octaves);

    const auto r5 = Perlin.accumulatedOctaveNoise2D_0_1((pos.x + 1) / freq, (pos.y + 1) / freq, octaves);
    const auto r6 = Perlin.accumulatedOctaveNoise2D_0_1((pos.x - 1) / freq, (pos.y + 1) / freq, octaves);
    const auto r7 = Perlin.accumulatedOctaveNoise2D_0_1((pos.x + 1) / freq, (pos.y - 1) / freq, octaves);
    const auto r8 = Perlin.accumulatedOctaveNoise2D_0_1((pos.x - 1) / freq, (pos.y - 1) / freq, octaves);

    return std::max({ r, r1, r2, r3, r4, r5, r6, r7, r8 }) == r;
}

unsigned Engine::Random::GetSquirrel1dNoise(int x, unsigned seed) {
    // Squirrel noise 3, taken from
    // https://www.youtube.com/watch?v=LWFzPP8ZbdU
    constexpr unsigned int BIT_NOISE1 = 0x68E31DA4;
    constexpr unsigned int BIT_NOISE2 = 0xB5297A4D;
    constexpr unsigned int BIT_NOISE3 = 0x1B56C4E9;

    auto mangledBits = static_cast<unsigned int>(x);
    mangledBits *= BIT_NOISE1;
    mangledBits += seed;
    mangledBits ^= (mangledBits >> 8);
    mangledBits += BIT_NOISE2;
    mangledBits ^= (mangledBits << 8);
    mangledBits *= BIT_NOISE3;
    mangledBits ^= (mangledBits >> 8);
    return mangledBits;
}

unsigned Engine::Random::GetSquirrel2dNoise(int x, int y, unsigned seed) {
    return Get1dNoise(x + PRIME1 * y, seed);
}
unsigned Engine::Random::GetSquirrel3dNoise(int x, int y, int z, unsigned seed) {
    return Get1dNoise(x + PRIME1 * y + PRIME2 * z, seed);
}
