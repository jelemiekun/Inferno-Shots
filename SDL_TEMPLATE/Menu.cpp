#include <iostream>
#include <SDL_image.h>
#include "Menu.h"
#include "MenuState.h"
#include "Game.h"

Menu::Menu() : currentState(nullptr) {}

Menu* Menu::getInstance() {
	static Menu instance;
	return &instance;
}

void Menu::initMenu() {
	Menu::getInstance()->setState(std::make_unique<MainMenu>());

	SDL_Texture* texture = IMG_LoadTexture(Game::getInstance()->getRenderer(), Menu::MENU_BG_PATH);

	if (!texture) {
		std::cerr << "Failed to create texture from surface: " << SDL_GetError() << '\n';
	} else {
		std::cout << "Texture with path " << Menu::MENU_BG_PATH << " loaded." << '\n';
	}

	Menu::getInstance()->mTexture.reset(texture);
}

void Menu::setState(std::unique_ptr<MenuState> state) {
	currentState = std::move(state);
}

void Menu::input() {
	currentState->input();
}

void Menu::update() {
	currentState->update();
}

void Menu::render() {
	currentState->render();
}