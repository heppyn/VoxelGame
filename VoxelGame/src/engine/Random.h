#pragma once

#include <random>
#include <perlin_noise/PerlinNoise.hpp>

namespace Engine
{
class Random
{
public:
    static siv::BasicPerlinNoise<float> Perlin;
    static unsigned Seed;
    static std::random_device RandomGen;

    static void Init();
    static void Init(unsigned seed);
};
}
