#include "GameState.h"
#include "InvokerPlaying.h"
#include "Game.h"

void GamePlaying::input() {
    SDL_Keycode keyCode = Game::getInstance()->getEvent().key.keysym.sym;
    InvokerPlaying::getInstance()->pressButton(keyCode);
}


void GamePlaying::update() {
    InvokerPlaying::getInstance()->updatePlayers();
}

void GamePlaying::render() {
    InvokerPlaying::getInstance()->renderPlayers();
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