#pragma once

#include "RandomGrammar.h"

namespace LSystems {
struct LSystem {
    Detail::RandomGrammar Grammar;
    float Yaw;
    float Pitch;
    float ShrinkRatio;

    LSystem(Detail::RandomGrammar&& grammar, float yaw, float pitch, float shrinkRatio)
        : Grammar(grammar), Yaw(yaw), Pitch(pitch), ShrinkRatio(shrinkRatio) {}
};
} // namespace LSystems
