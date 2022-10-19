#include <engine/EntryPoint.h>

#include "Game.h"


Game* Engine::CreateGame() {
    return new App;
}
