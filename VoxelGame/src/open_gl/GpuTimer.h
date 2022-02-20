#pragma once

namespace OpenGl {
class GpuTimer {
  public:
    GpuTimer();
    void Start() const;
    void Stop();
    [[nodiscard]] long long Time();
    [[nodiscard]] float TimeMs();

  private:
    unsigned QueryId_[2];
    bool Stopped_{ false };
};
} // namespace OpenGl
