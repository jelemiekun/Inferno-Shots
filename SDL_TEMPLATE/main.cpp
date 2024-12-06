#include <SDL.h>
#include "Game.h"
#include "FPSManager.h"

// TODO: player name input
// TODO: save game state of the game such as player name, player position, and wave number
// TODO: load saved game state
// TODO: cooldown in firing, higher wave, shorter cooldown
// TODO: enemy difficulty, add fast enemies beyond wave 3
// TODO: subtract random number in total enemies then using that random number, generate amount of fast enemies
// TODO: big boss in every 5 rounds
// TODO: 5th round = 1 big boss, 10th round = 2 big boss, 15th round = 3 big boss...
// TODO: Menu State     = New Game / Load Game / Exit
// TODO: Paused State   = Continue / Save State / Return to Menu
// TODO: Game Over      = Play Again / Return to Menu 
// TODO: music & sfx

int SDL_main(int argc, char* argv[]) {
    Game* game = Game::getInstance();
    game->init();

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