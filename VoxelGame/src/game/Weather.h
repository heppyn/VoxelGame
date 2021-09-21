#pragma once

namespace Weather {
struct Humidity {
  public:
    static const unsigned char SIZE{ 10 };

    unsigned char Value;
};

struct Temperature {
  public:
    static const unsigned char SIZE{ 10 };

    unsigned char Value;
};
} // namespace Weather
