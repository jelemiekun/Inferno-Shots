#include "MenuState.h"
#include "Game.h"
#include "Menu.h"

void MenuState::render() {
	SDL_RenderCopy(Game::getInstance()->getRenderer(), Menu::getInstance()->mTexture.get(), nullptr, nullptr);
}

void MainMenu::input() {

}

void MainMenu::update() {

}

void MainMenu::render() {
	MenuState::render();
}

void TextInputMenu::input() {

}

void TextInputMenu::update() {

}

void TextInputMenu::render() {
	MenuState::render();
}

void PausedMenu::input() {

}

void PausedMenu::update() {

}

void PausedMenu::render() {

}

void GameOverMenu::input() {

}

void GameOverMenu::update() {

}

void GameOverMenu::render() {

}