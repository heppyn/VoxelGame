#pragma once
#include <vector>

#include "GameObject.h"

class Scene {
  private:
    std::vector<GameObject> Lights_{};
    std::vector<GameObject> Objects_{};

  public:
    void Init();

    [[nodiscard]] std::vector<GameObject>& GetLights() {
        return Lights_;
    }

    [[nodiscard]] const std::vector<GameObject>& GetLights() const {
        return Lights_;
    }

    [[nodiscard]] std::vector<GameObject>& GetObjects() {
        return Objects_;
    }

    [[nodiscard]] const std::vector<GameObject>& GetObjects() const {
        return Objects_;
    }
};
