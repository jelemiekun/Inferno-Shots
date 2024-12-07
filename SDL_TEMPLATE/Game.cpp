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
#include "Background.h"
#include "Bullet.h"
#include "Enemy.h"
#include "NormalEnemy.h"
#include "Minimap.h"
#include "WaveManager.h"
#include "PlayerProfile.h"
#include "Text.h"

Game::Game() : gWindow(nullptr), gRenderer(nullptr), gameState(std::make_unique<GamePlaying>()),
				running(false) {}

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

void Game::initFonts() {
	Text::initFonts();
	WaveManager::initTexts();
}

void Game::setRunningToTrue() {
	running = true;
}

void Game::setRunningToFalse() {
	running = false;
}

void Game::initBackground() {
	Background::getInstance()->init();
}

void Game::initPlayerProfile() {
	PlayerProfile::loadPlayerProfiles();
}

void Game::initPlayer() {
	// Initialize main prototype of Player
	SDL_Point position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	TextureType* playerTexture = new TextureType(Prototype_Type::PLAYER);
	std::shared_ptr<Player> playerPrototype = std::make_shared<Player>(100, 200, playerTexture, position, 4.0f, 30.0f);

	// Add main prototype player to Prototype Registry
	PrototypeRegistry::getInstance()->addPrototype(
		Prototype_Type::PLAYER, std::static_pointer_cast<Prototype>(playerPrototype)
	);

	// Clone a player
	std::shared_ptr<Player> player1 = std::dynamic_pointer_cast<Player>(
		PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::PLAYER)
	);
	
	player1->initProfile();

	// Add player to invoker
	InvokerPlaying::getInstance()->addPlayer(player1);

	//{
	//	// Clone a player
	//	std::shared_ptr<Player> player2 = std::dynamic_pointer_cast<Player>(
	//		PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::PLAYER)
	//	);

	//	player2->initProfile();

	//	// Add player to invoker
	//	InvokerPlaying::getInstance()->addPlayer(player2);

	//	// Clone a player
	//	std::shared_ptr<Player> player3 = std::dynamic_pointer_cast<Player>(
	//		PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::PLAYER)
	//	);

	//	player3->initProfile();

	//	// Add player to invoker
	//	InvokerPlaying::getInstance()->addPlayer(player3);

	//	// Clone a player
	//	std::shared_ptr<Player> player4 = std::dynamic_pointer_cast<Player>(
	//		PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::PLAYER)
	//	);

	//	player4->initProfile();

	//	// Add player to invoker
	//	InvokerPlaying::getInstance()->addPlayer(player4);
	//}

	// Set commands
	auto moveLeftCommand = std::make_shared<MoveLeftCommand>();
	auto moveUpCommand = std::make_shared<MoveUpCommand>();
	auto moveRightCommand = std::make_shared<MoveRightCommand>();
	auto moveDownCommand = std::make_shared<MoveDownCommand>();

	auto keyUpMoveLeftCommand = std::make_shared<KeyUpMoveLeftCommand>();
	auto keyUpMoveUpCommand = std::make_shared<KeyUpMoveUpCommand>();
	auto keyUpMoveRightCommand = std::make_shared<KeyUpMoveRightCommand>();
	auto keyUpMoveDownCommand = std::make_shared<KeyUpMoveDownCommand>();

	auto faceLeftCommand = std::make_shared<FaceLeftCommand>();
	auto faceUpLeftCommand = std::make_shared<FaceUpLeftCommand>();
	auto faceUpCommand = std::make_shared<FaceUpCommand>();
	auto faceUpRightCommand = std::make_shared<FaceUpRightCommand>();
	auto faceRightCommand = std::make_shared<FaceRightCommand>();
	auto faceDownRightCommand = std::make_shared<FaceDownRightCommand>();
	auto faceDownCommand = std::make_shared<FaceDownCommand>();
	auto faceDownLeftCommand = std::make_shared<FaceDownLeftCommand>();


	auto sprintCommand = std::make_shared<SprintCommand>();
	auto removeSprintCommand = std::make_shared<RemoveSprintCommand>();

	auto fireCommand = std::make_shared<FireCommand>();

	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_a, moveLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_w, moveUpCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_d, moveRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_s, moveDownCommand, player1);

	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_f, faceLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_r, faceUpLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_t, faceUpCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_y, faceUpRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_h, faceRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_n, faceDownRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_b, faceDownCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_v, faceDownLeftCommand, player1);

	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_j, keyUpMoveLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_i, keyUpMoveUpCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_l, keyUpMoveRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_k, keyUpMoveDownCommand, player1);

	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_LSHIFT, sprintCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_CAPSLOCK, removeSprintCommand, player1);
	
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_x, fireCommand, player1);
}

void Game::initBullet() {
	std::shared_ptr<Bullet> bulletPrototype = std::make_shared<Bullet>();

	PrototypeRegistry::getInstance()->addPrototype(
		Prototype_Type::BULLET, std::static_pointer_cast<Prototype>(bulletPrototype)
	);
}

void Game::initEnemy() {
	std::shared_ptr<TextureType> normalEnemyTexture = std::make_shared<TextureType>(Prototype_Type::NORMAL_ENEMY);
	std::shared_ptr<NormalEnemy> normalEnemyPrototype = std::make_shared<NormalEnemy>(normalEnemyTexture);

	PrototypeRegistry::getInstance()->addPrototype(
		Prototype_Type::NORMAL_ENEMY, std::static_pointer_cast<Prototype>(normalEnemyPrototype)
	);
}

void Game::initMiniMap() {
	Minimap::getInstance()->initMinimap();
}

void Game::initBars() {
	WaveManager::getInstance()->initCountdownBar();
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
	initFonts();
	setRunningToTrue();
	initBackground();
	initPlayerProfile();
	initPlayer();
	initBullet();
	initEnemy();
	initMiniMap();
	initBars();
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
	Minimap::getInstance()->update();
}

void Game::render() {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderClear(gRenderer);

	Background::getInstance()->render();
	gameState->render();
	Minimap::getInstance()->render();

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