#pragma once
#include <cstdint>
#include <compare>

namespace Engine::Cube {
enum class Faces {
    ALL,
    TOP,
    BOTTOM,
    FRONT,
    BACK,
    LEFT,
    RIGHT
};

/**
 * \brief Represents faces of a cube
 * is created by it's factory method
 */
class BlockFaces {
  public:
    const uint8_t Value;

    BlockFaces() = delete;

    template<typename... Types>
    static BlockFaces CreateBlockFaces(Types... faces) {
        return GenerateBlockFaces(0, faces...);
    }

    [[nodiscard]] bool HasFace(Faces face) const;

    auto operator<=>(const BlockFaces& other) const = default;

  private:
    // can be only created from factory method
    explicit BlockFaces(uint8_t value);

    static BlockFaces GenerateBlockFaces(uint8_t value, Faces face) {
        return BlockFaces(SetBlockFace(value, face));
    }

    template<typename... Types>
    static BlockFaces GenerateBlockFaces(uint8_t value, Faces face, Types... faces) {
        return GenerateBlockFaces(SetBlockFace(value, face), faces...);
    }

    static uint8_t SetBlockFace(uint8_t value, Faces face);
};

const BlockFaces ALL_SIDES = BlockFaces::CreateBlockFaces(Faces::ALL);
const BlockFaces PIPE = BlockFaces::CreateBlockFaces(Faces::FRONT, Faces::BACK, Faces::LEFT, Faces::RIGHT);
} // namespace Engine::Cube
