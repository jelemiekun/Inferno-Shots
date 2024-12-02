#include <iostream>
#include <SDL_image.h>
#include "Game.h"
#include "GameState.h"
#include "AppInfo.h"
#include "Invoker.h"
#include "Prototype.h"
#include "PrototypeRegistry.h"







Game::Game() : gWindow(nullptr), gRenderer(nullptr), gameState(std::make_unique<GamePlaying>()),
				running(false), gFont(nullptr) {}

void Game::initSDLSubsystems() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << "Failed to initialize SDL subsystems." << SDL_GetError() << '\n';
	else
		std::cout << "Initialized SDL subsystems." << '\n';
}

void Game::initWindowCreation() {
	gWindow = SDL_CreateWindow(
		TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (!gWindow) std::cout << "Failed to create window: " << SDL_GetError() << '\n';
	else std::cout << "Window created." << '\n';
}

void Game::initRendererCreation() {
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!gRenderer) std::cout << "Failed to create renderer: " << SDL_GetError() << '\n';
	else std::cout << "Renderer created." << '\n';
}

void Game::initSDL_image() {
	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags)) std::cout << "Warning: SDL_image could not initialize: " << IMG_GetError() << '\n';
	else std::cout << "SDL_image initialized." << '\n';
}

void Game::initSDL_ttf() {
	if (TTF_Init() == -1) std::cout << "SDL_TTF could not initialize: " << TTF_GetError() << '\n';
	else std::cout << "SDL_TTF initialized." << '\n';
}

void Game::initGFont() {
	//TODO
	gFont = TTF_OpenFont("path", 28);

	if (!gFont) std::cout << "Failed to load font: " << TTF_GetError() << '\n';
	else std::cout << "Font loaded." << '\n';
}

void Game::setRunningToTrue() {
	running = true;
}

void Game::setRunningToFalse() {
	running = false;
}

Game* Game::getInstance() {
	static Game instance;
	return &instance;
}

void Game::init() {
	initSDLSubsystems();
	initWindowCreation();
	initRendererCreation();
	initSDL_image();
	initSDL_ttf();
	initGFont();
	setRunningToTrue();

	{
		SDL_Point position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		std::shared_ptr<Player> playerPrototype = std::make_shared<Player>(5, position, 5.0f, 30.0f);

		// Register the Player prototype
		PrototypeRegistry::getInstance()->addPrototype(
			Prototype_Type::PLAYER, std::static_pointer_cast<Prototype>(playerPrototype)
		);


		std::shared_ptr<Player> clonedPlayer = std::dynamic_pointer_cast<Player>(
			PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::PLAYER)
		);

		Invoker::getInstance()->addPlayer(clonedPlayer);
	}
}

void Game::input() {
	while (SDL_PollEvent(&gEvent)) {
		if (gEvent.type == SDL_QUIT) {
			setRunningToFalse();
		}

		gameState->input();
	}
}

void Game::update() {
	gameState->update();
}

void Game::render() {
	gameState->render();
}

const SDL_Renderer* Game::getRenderer() const {
	return gRenderer;
}

const SDL_Event& Game::getEvent() const {
	return gEvent;
}

const bool& Game::isRunning() const {
	return running;
}