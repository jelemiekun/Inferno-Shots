#include <SDL.h>
#include "Game.h"
#include "FPSManager.h"

// TODO : save game state of the game such as player name, player position, and wave number 
// TODO : music & sfx
// TODO : compress photos/audios
// TODO : controller

int SDL_main(int argc, char* argv[]) {
    Game* game = Game::getInstance();
    game->initAll();

    int countFramme = 0;
    Uint32 startTime = SDL_GetTicks();


    while (game->isRunning()) {
        Uint32 frameStart = SDL_GetTicks();

        game->input();
        game->update();
        game->render();

        FPSManager::limitFPS(frameStart);
        FPSManager::calculateAverageFPS(countFramme, startTime);
    }

    return 0;
}