#include "PerlinTest.h"

#include <iostream>

#include "engine/Random.h"

void Tests::PerlinTest::RunTests() {
    PrintTable();
}

void Tests::PerlinTest::PrintTable() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            std::cout << Engine::Random::Perlin.noise2D((float)i / 10.0f, (float)j/ 10.0f) << ' ';
        }
        std::cout << '\n';
    }
}
