#include <iostream>
#include <SDL_image.h>
#include "Menu.h"
#include "MenuState.h"
#include "Game.h"
#include "Text.h"
#include "Player.h"

std::string Menu::tempPlayerNamme = " ";

Menu::Menu() : currentState(std::make_unique<MainMenu>()),
	menuBackgroundDimension(nullptr),
	pauseGODimension(nullptr),
	mainMenuFlags(nullptr),
	changeNameFlags(nullptr),
	pauseFlags(nullptr),
	gameOverFlags(nullptr),
	playerNameText(nullptr)
	{}

Menu* Menu::getInstance() {
	static Menu instance;
	return &instance;
}

void Menu::initTexture(
	const char* filePath,
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>& texture,
	std::unique_ptr<SDL_Point>& dimension
) {
	SDL_Texture* rawTexture = IMG_LoadTexture(Game::getInstance()->getRenderer(), filePath);

	if (!rawTexture) {
		std::cerr << "Failed to create texture from file " << filePath << ": " << SDL_GetError() << '\n';
		return;
	}

	std::cout << "Texture loaded from path: " << filePath << '\n';
	texture.reset(rawTexture);

	dimension = std::make_unique<SDL_Point>();
	SDL_QueryTexture(texture.get(), nullptr, nullptr, &dimension->x, &dimension->y);
}

void Menu::initFlags() {
	mouseStateFlags = std::make_unique<MouseStateFlags>();
	mainMenuFlags = std::make_unique<MainMenuFlags>();
	changeNameFlags = std::make_unique<ChangeNameFlags>();
	pauseFlags = std::make_unique<PauseFlags>();
	gameOverFlags = std::make_unique<GameOverFlags>();
}

void Menu::initPlayerNameText() {
	playerNameText = std::make_unique<Text>();

	playerNameText->setFont(Font::MOTION_CONTROL_BOLD);
	playerNameText->setDstRect({ 318, 360, 260, 60 });
	playerNameText->setColor({ 0, 0, 0, 255 });
}

void Menu::changePlayerName() {
	Player::staticStringPlayerName = tempPlayerNamme;
}

void Menu::resetFlags() {
	Menu::tempPlayerNamme = Player::staticStringPlayerName;

	mouseStateFlags->outside = 1;
	mouseStateFlags->clicked = 0;

	mainMenuFlags->play = 1;
	mainMenuFlags->loadGame = 0;
	mainMenuFlags->changeName = 0;
	mainMenuFlags->exit = 0;

	changeNameFlags->change = 1;
	changeNameFlags->cancel = 0;

	pauseFlags->resume = 0;
	pauseFlags->saveGame = 1;
	pauseFlags->exit = 1;

	gameOverFlags->playAgain = 0;
	gameOverFlags->mainMenu = 1;
}

void Menu::initMenu() {
	initTexture(
		MENU_BG_PATH, 
		mTextureMenu,
		menuBackgroundDimension
	);

	initTexture(
		PAUSE_GO_BG_PATH, 
		mTexturePauseGO,
		pauseGODimension
	);

	initFlags();
	resetFlags();
	initPlayerNameText();
	setState(std::make_unique<MainMenu>());
}

void Menu::setState(std::unique_ptr<MenuState> state) {
	resetFlags();
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