#include <engine/Game.h>


#define USE_TERRAIN_GEN

class App : public Game {
  public:
    App() = default;
    ~App() override;
    void Init() override;
};
