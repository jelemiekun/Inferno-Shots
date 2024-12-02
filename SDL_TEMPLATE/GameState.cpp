#include "GameState.h"
#include "Invoker.h"
#include "Game.h"

void GamePlaying::input() {
    SDL_Keycode keyCode = Game::getInstance()->getEvent().key.keysym.sym;
    Invoker::getInstance()->pressButton(keyCode);
}


void GamePlaying::update() {
    Invoker::getInstance()->updatePlayers();
}

void GamePlaying::render() {
    Invoker::getInstance()->renderPlayers();
}

void GamePaused::input() {

}

void GamePaused::update() {

}

void GamePaused::render() {

}

void GameOver::input() {

}

void GameOver::update() {

}

void GameOver::render() {

}