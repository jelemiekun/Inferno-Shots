#include "GameState.h"
#include "Invoker.h"
#include "Game.h"

void GamePlaying::input() {
    SDL_Keycode keyCode = Game::getInstance()->getEvent().key.keysym.sym;
    Invoker::getInstance()->pressButton(keyCode);
}


void GamePlaying::update() {

}

void GamePlaying::render() {

}

void GamePaused::input() {

}

void GamePaused::update() {

}

void GamePaused::render() {

}