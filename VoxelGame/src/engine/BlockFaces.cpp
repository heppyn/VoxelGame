#include "BlockFaces.h"

#include <cassert>

//int Engine::Cube::BlockFaces::operator<=>(const BlockFaces& other) const {
//    return Value <=> other.Value;
//}

Engine::Cube::BlockFaces::BlockFaces(uint8_t value)
  : Value(value) {}

uint8_t Engine::Cube::BlockFaces::SetBlockFace(uint8_t value, Faces face) {
    switch (face) {
        case Faces::ALL:
            return 0b00111111;
        case Faces::TOP:
            return value | 0b00100000;
        case Faces::BOTTOM:
            return value | 0b00010000;
        case Faces::FRONT:
            return value | 0b00001000;
        case Faces::BACK:
            return value | 0b00000100;
        case Faces::LEFT:
            return value | 0b00000010;
        case Faces::RIGHT:
            return value | 0b00000001;
    }

    assert(false && "Wrong definition of enum Faces");
    return 0;
}
