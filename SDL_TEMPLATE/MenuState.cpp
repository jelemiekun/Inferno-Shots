#include "MenuState.h"
#include "Game.h"
#include "GameState.h"
#include "Menu.h"
#include "Selector.h"
#include <iostream>

void MainMenu::input() {
	MouseStateFlags* mouseFlags = Menu::getInstance()->mouseStateFlags.get();
	MainMenuFlags* menuFlags = Menu::getInstance()->mainMenuFlags.get();

	static int MPX, MPY = 0; // Mouse Position X/Y
	switch (Game::getInstance()->getEvent().type) {
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&MPX, &MPY);

		if (MPX >= 530 && MPX <= 630 && MPY >= 360 && MPY <= 415) {
			mouseFlags->outside = 0;
			menuFlags->play = 1;
			menuFlags->loadGame = 0;
			menuFlags->changeName = 0;
			menuFlags->exit = 0;
		} else if (MPX >= 465 && MPX <= 710 && MPY >= 428 && MPY <= 483) {
			mouseFlags->outside = 0;
			menuFlags->play = 0;
			menuFlags->loadGame = 1;
			menuFlags->changeName = 0;
			menuFlags->exit = 0;
		} else if (MPX >= 445 && MPX <= 730 && MPY >= 498 && MPY <= 553) {
			mouseFlags->outside = 0;
			menuFlags->play = 0;
			menuFlags->loadGame = 0;
			menuFlags->changeName = 1;
			menuFlags->exit = 0;
		} else if (MPX >= 532 && MPX <= 642 && MPY >= 566 && MPY <= 621) {
			mouseFlags->outside = 0;
			menuFlags->play = 0;
			menuFlags->loadGame = 0;
			menuFlags->changeName = 0;
			menuFlags->exit = 1;
		} else {
			mouseFlags->outside = 1;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (Game::getInstance()->getEvent().button.button == SDL_BUTTON_LEFT) {
			mouseFlags->clicked = 1;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (Game::getInstance()->getEvent().button.button == SDL_BUTTON_LEFT) {
			mouseFlags->clicked = 0;
		}
		break;
	default:
		break;
	}
}

void MainMenu::update() {
	Menu* menu = Menu::getInstance();
	if (menu->mainMenuFlags->play) {
		Selector::getInstance()->update(70, 376);

		if (!menu->mouseStateFlags->outside && menu->mouseStateFlags->clicked) {
			Game::getInstance()->setState(std::make_unique<GamePlaying>());
		}
	} else if (menu->mainMenuFlags->loadGame) {
		Selector::getInstance()->update(140, 445);

		/*if (!menu->mouseStateFlags->outside && menu->mouseStateFlags->clicked) {
			Game::getInstance()->setState(std::make_unique<GamePlaying>());
		}*/ // TODO: check if there'es saved game
	} else if (menu->mainMenuFlags->changeName) {
		Selector::getInstance()->update(160, 515);

		if (!menu->mouseStateFlags->outside && menu->mouseStateFlags->clicked) {
			menu->setState(std::make_unique<TextInputMenu>());
		}
	} else if (menu->mainMenuFlags->exit) {
		Selector::getInstance()->update(72, 583);

		if (!menu->mouseStateFlags->outside && menu->mouseStateFlags->clicked) {
			Game::getInstance()->setRunningToFalse();
		}
	}
}

void MainMenu::render() {
	SDL_Rect srcRect = { 0, 0,
		Menu::getInstance()->menuBackgroundDimension->x / 2, Menu::getInstance()->menuBackgroundDimension->y };

	SDL_RenderCopy(Game::getInstance()->getRenderer(), Menu::getInstance()->mTextureMenu.get(), &srcRect, nullptr );
	Selector::getInstance()->render();

	/*SDL_SetRenderDrawBlendMode(Game::getInstance()->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::getInstance()->getRenderer(), 255, 0, 0, 120);
	SDL_Rect tester = {
		532, 566, 110, 55
	};
	SDL_RenderFillRect(Game::getInstance()->getRenderer(), &tester);*/
}

void TextInputMenu::input() {

}

void TextInputMenu::update() {

}

void TextInputMenu::render() {
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
	SDL_Rect srcRect = { Menu::getInstance()->menuBackgroundDimension->x / 2, 0,
		Menu::getInstance()->menuBackgroundDimension->x / 2, Menu::getInstance()->menuBackgroundDimension->y };

	SDL_RenderCopy(Game::getInstance()->getRenderer(), Menu::getInstance()->mTextureMenu.get(), &srcRect, nullptr);
}