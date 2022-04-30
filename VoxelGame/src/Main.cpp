#include "engine/EntryPoint.h"
#include "engine/Game.h"


/**
 * \brief Example app.
 * You can redefine methods of the Game.
 */
class App : public Game {
};

Game* Engine::CreateGame() {
    return new App;
}
