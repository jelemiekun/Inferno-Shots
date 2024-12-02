#include <iostream>
#include <SDL_image.h>
#include "Game.h"
#include "GameState.h"
#include "AppInfo.h"
#include "InvokerPlaying.h"
#include "Prototype.h"
#include "PrototypeRegistry.h"
#include "TextureType.h"
#include "Command.h"





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

void Game::initPlayer() {
	// Initialize main prototype of Player
	SDL_Point position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	TextureType* playerTexture = new TextureType(Prototype_Type::PLAYER);
	std::shared_ptr<Player> playerPrototype = std::make_shared<Player>(5, playerTexture, position, 5.0f, 30.0f);

	// Add main prototype player to Prototype Registry
	PrototypeRegistry::getInstance()->addPrototype(
		Prototype_Type::PLAYER, std::static_pointer_cast<Prototype>(playerPrototype)
	);

	// Clone a player
	std::shared_ptr<Player> player1 = std::dynamic_pointer_cast<Player>(
		PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::PLAYER)
	);

	// Add player to invoker
	InvokerPlaying::getInstance()->addPlayer(player1);

	// Set commands
	auto moveLeftCommand = std::make_shared<MoveLeftComand>();
	auto moveUpLeftCommand = std::make_shared<MoveUpLeftComand>();
	auto moveUpCommand = std::make_shared<MoveUpComand>();
	auto moveUpRightCommand = std::make_shared<MoveUpRightComand>();
	auto moveRightCommand = std::make_shared<MoveRightComand>();
	auto moveDownRightCommand = std::make_shared<MoveDownRightComand>();
	auto moveDownCommand = std::make_shared<MoveDownComand>();
	auto moveDownLeftCommand = std::make_shared<MoveDownLeftComand>();

	auto faceLeftCommand = std::make_shared<FaceLeftComand>();
	auto faceUpLeftCommand = std::make_shared<FaceUpLeftComand>();
	auto faceUpCommand = std::make_shared<FaceUpComand>();
	auto faceUpRightCommand = std::make_shared<FaceUpRightComand>();
	auto faceRightCommand = std::make_shared<FaceRightComand>();
	auto faceDownRightCommand = std::make_shared<FaceDownRightComand>();
	auto faceDownCommand = std::make_shared<FaceDownComand>();
	auto faceDownLeftCommand = std::make_shared<FaceDownLeftComand>();

	std::shared_ptr<SprintCommand> sprintCommand = std::make_shared<SprintCommand>();
	std::shared_ptr<FireCommans> fireCommand = std::make_shared<FireCommans>();

	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_w, moveUpCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_a, moveLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_s, moveDownCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_d, moveRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_q, moveUpLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_e, moveUpRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_z, moveDownLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_c, moveDownRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_LSHIFT, sprintCommand, player1);
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
	initPlayer();
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
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderClear(gRenderer);

	gameState->render();

	SDL_RenderPresent(gRenderer);
}

SDL_Renderer* Game::getRenderer() {
	return gRenderer;
}

const SDL_Event& Game::getEvent() const {
	return gEvent;
}

const bool& Game::isRunning() const {
	return running;
}