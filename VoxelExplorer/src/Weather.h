#pragma once

/**
 * \brief Represents humidity and temperature as discrete values
 */
namespace Weather {
static constexpr unsigned NOISE{ 5 };

struct Humidity {
  public:
    static constexpr unsigned char SIZE{ 10 };

    unsigned char Value;
};

struct Temperature {
  public:
    static constexpr unsigned char SIZE{ 10 };

    unsigned char Value;
};
} // namespace Weather
