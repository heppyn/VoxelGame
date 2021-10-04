#pragma once

#include <random>
#include <limits>
#include <perlin_noise/PerlinNoise.hpp>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

namespace Engine {
class Random {
  public:
    static siv::BasicPerlinNoise<float> Perlin;
    static unsigned Seed;
    //TODO: get rid of this - not PRNG - too slow
    static std::random_device RandomGen;

    static void Init();
    static void Init(unsigned seed);
    static bool IsLocalMaxPerlin(const glm::vec2& pos, float freq, int octaves);

    // convert T to int. static_cast<unsigned int>(-1.0f) == 0u
    template<typename T>
    static unsigned int Get1dNoise(T x, unsigned int seed = Seed) {
        return GetSquirrel1dNoise(static_cast<int>(x), seed);
    }
    template<typename T>
    static unsigned int Get2dNoise(T x, T y, unsigned int seed = Seed) {
        return GetSquirrel2dNoise(static_cast<int>(x), static_cast<int>(y), seed);
    }
    template<typename T>
    static unsigned int Get3dNoise(T x, T y, T z, unsigned int seed = Seed) {
        return GetSquirrel3dNoise(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z), seed);
    }

    template<typename T, typename Y>
    static T Get1dNoise0_1(Y x, unsigned int seed = Seed) {
        return static_cast<T>(Get1dNoise(x, seed)) / static_cast<T>(std::numeric_limits<unsigned int>::max());
    }
    template<typename T, typename Y>
    static T Get2dNoise0_1(Y x, Y y, unsigned int seed = Seed) {
        return static_cast<T>(Get2dNoise(x, y, seed)) / static_cast<T>(std::numeric_limits<unsigned int>::max());
    }
    template<typename T, typename Y>
    static T Get3dNoise0_1(Y x, Y y, Y z, unsigned int seed = Seed) {
        return static_cast<T>(Get3dNoise(x, y, z, seed)) / static_cast<T>(std::numeric_limits<unsigned int>::max());
    }

    template<typename T, typename Y>
    static T GetNoise0_1(T, unsigned int seed = Seed) = delete;

    template<typename T>
    static T GetNoise0_1(const glm::vec2& vec, unsigned int seed = Seed) {
        return Get2dNoise0_1<T>(vec.x, vec.y, seed);
    }

    template<typename T>
    static T GetNoise0_1(const glm::vec3& vec, unsigned int seed = Seed) {
        return Get3dNoise0_1<T>(vec.x, vec.y, vec.z, seed);
    }


  private:
    static constexpr int PRIME1 = 198491317; // large prime number with non-boring bits
    static constexpr int PRIME2 = 6542989; // large prime number with non-boring bits

    static unsigned int GetSquirrel1dNoise(int x, unsigned int seed);
    static unsigned int GetSquirrel2dNoise(int x, int y, unsigned int seed);
    static unsigned int GetSquirrel3dNoise(int x, int y, int z, unsigned int seed);
};
} // namespace Engine
