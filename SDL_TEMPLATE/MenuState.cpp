#include "MenuState.h"
#include "Game.h"
#include "GameState.h"
#include "Menu.h"
#include "Selector.h"
#include "Text.h"
#include "BorderManager.h"
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
	// TODO tester rects
}

void TextInputMenu::input() {
	SDL_StartTextInput();

	MouseStateFlags* mouseFlags = Menu::getInstance()->mouseStateFlags.get();
	ChangeNameFlags* nameFlags = Menu::getInstance()->changeNameFlags.get();
	SDL_Event event = Game::getInstance()->getEvent();
	std::string& playerName = Menu::tempPlayerNamme;

	static int MPX, MPY = 0; // Mouse Position X/Y
	switch (event.type) {
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&MPX, &MPY);

		if (MPX >= 480 && MPX <= 700 && MPY >= 465 && MPY <= 520) {
			mouseFlags->outside = 0;
			nameFlags->change = 1;
			nameFlags->cancel = 0;
		} else if (MPX >= 480 && MPX <= 700 && MPY >= 540 && MPY <= 595) {
			mouseFlags->outside = 0;
			nameFlags->change = 0;
			nameFlags->cancel = 1;
		}else {
			mouseFlags->outside = 1;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) {
			mouseFlags->clicked = 1;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT) {
			mouseFlags->clicked = 0;
		}
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_BACKSPACE && !playerName.empty()) {
			playerName.pop_back();
		}
		break;
	case SDL_TEXTINPUT:
		if (playerName.length() < Menu::MAX_INPUT_LENGTH) {
			playerName += event.text.text;
		}
		break;
	default:
		break;
	}
}

void TextInputMenu::update() {
	Menu* menu = Menu::getInstance();

	if (menu->changeNameFlags->change) {
		Selector::getInstance()->update(110, 482);

		if (!menu->mouseStateFlags->outside && menu->mouseStateFlags->clicked) {
			Menu::getInstance()->changePlayerName();
			Menu::getInstance()->setState(std::make_unique<MainMenu>());
		}
	} else if (menu->changeNameFlags->cancel) {
		Selector::getInstance()->update(110, 555);

		if (!menu->mouseStateFlags->outside && menu->mouseStateFlags->clicked) {
			Menu::getInstance()->setState(std::make_unique<MainMenu>());
		}
	}

	Menu::getInstance()->playerNameText->setText(Menu::tempPlayerNamme);
	Menu::getInstance()->playerNameText->loadText();
}

void TextInputMenu::render() {
	SDL_Rect srcRect = { Menu::getInstance()->menuBackgroundDimension->x / 2, 0,
		Menu::getInstance()->menuBackgroundDimension->x / 2, Menu::getInstance()->menuBackgroundDimension->y };

	SDL_RenderCopy(Game::getInstance()->getRenderer(), Menu::getInstance()->mTextureMenu.get(), &srcRect, nullptr);
	Selector::getInstance()->render();

	Menu::getInstance()->playerNameText->render();
}

void PausedMenu::input() {

}

void PausedMenu::update() {

}

void PausedMenu::render() {
	SDL_Renderer* renderer = Game::getInstance()->getRenderer();
	SDL_Rect* dstRect = Menu::getInstance()->pausedGameOverDstRect.get();

	SDL_Rect srcRect = { 0, 0,
		Menu::getInstance()->pauseGODimension->x / 2, Menu::getInstance()->pauseGODimension->y };

	SDL_RenderCopy(renderer, Menu::getInstance()->mTexturePauseGO.get(), &srcRect, dstRect);

	Border::bRenderBorder(renderer, *dstRect, 3, { 0, 0, 0, 255 } );
}

void GameOverMenu::input() {

}

void GameOverMenu::update() {

}

void GameOverMenu::render() {
	SDL_Renderer* renderer = Game::getInstance()->getRenderer();
	SDL_Rect* dstRect = Menu::getInstance()->pausedGameOverDstRect.get();

	SDL_Rect srcRect = { Menu::getInstance()->pauseGODimension->x / 2, 0,
		Menu::getInstance()->pauseGODimension->x / 2, Menu::getInstance()->pauseGODimension->y };

	SDL_RenderCopy(renderer, Menu::getInstance()->mTexturePauseGO.get(), &srcRect, dstRect);

	Border::bRenderBorder(renderer, *dstRect, 3, { 0, 0, 0, 255 });
}