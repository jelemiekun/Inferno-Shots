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
#include "EnemyType.h"
#include "Minimap.h"
#include "WaveManager.h"
#include "PlayerProfile.h"
#include "Text.h"
#include "FastEnemy.h"
#include "Menu.h"
#include "Selector.h"
#include "GameProgressManager.h"
#include "GameProgress.h"
#include "GameSound.h"
#include <cstring> 

Game::Game() : gWindow(nullptr), gRenderer(nullptr), gameState(std::make_unique<GameMenu>()),
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

void Game::initGameSound() {
	GameSound::getInstance()->initMixer();
}

void Game::setRunningToTrue() {
	running = true;
}

void Game::setRunningToFalse() {
	running = false;
}

void Game::initMenu() {
	Menu::getInstance()->initMenu();
}

void Game::initSelector() {
	Selector::getInstance()->init();
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
	std::shared_ptr<Player> playerPrototype = std::make_shared<Player>(1, 700, position, 4.0f, 30.0f);

	// Add main prototype player to Prototype Registry
	PrototypeRegistry::getInstance()->addPrototype(
		Prototype_Type::PLAYER, std::static_pointer_cast<Prototype>(playerPrototype)
	);
}

void Game::initBullet() {
	std::shared_ptr<Bullet> bulletPrototype = std::make_shared<Bullet>();

	PrototypeRegistry::getInstance()->addPrototype(
		Prototype_Type::BULLET, std::static_pointer_cast<Prototype>(bulletPrototype)
	);
}

void Game::initEnemy() {
	// Normal Enemy
	{
		// Normal Enemy
		std::shared_ptr<TextureType> normalEnemyTexture = std::make_shared<TextureType>(Prototype_Type::NORMAL_ENEMY);
		std::shared_ptr<EnemyType> normalEnemyPrototype = std::make_shared<EnemyType>(Prototype_Type::NORMAL_ENEMY, 
			normalEnemyTexture, SDL_Point{ 30, 30 }, 1, 3.0F, 7, 3, 3);
		PrototypeRegistry::getInstance()->addPrototype(
			Prototype_Type::NORMAL_ENEMY, std::static_pointer_cast<Prototype>(normalEnemyPrototype)
		);

		// Normal Enemy Fast
		std::shared_ptr<Enemy> clonedNormalEnemy = std::static_pointer_cast<Enemy>(normalEnemyPrototype->clone());
		std::shared_ptr<FastEnemy> fastNormalEnemyPrototype = std::make_shared<FastEnemy>(clonedNormalEnemy);

		PrototypeRegistry::getInstance()->addPrototype(
			Prototype_Type::NORMAL_ENEMY_FAST, std::static_pointer_cast<Prototype>(fastNormalEnemyPrototype)
		);
	}
    
	// Medium Enemy
	{
		// Medium Enemy
		std::shared_ptr<TextureType> mediumEnemyTexture = std::make_shared<TextureType>(Prototype_Type::MEDIUM_ENEMY);
		std::shared_ptr<EnemyType> mediumEnemyPrototype = std::make_shared<EnemyType>(Prototype_Type::MEDIUM_ENEMY, 
			mediumEnemyTexture, SDL_Point{ 78, 78 }, 4, 5.0F, 16, 11, 5);
		PrototypeRegistry::getInstance()->addPrototype(
			Prototype_Type::MEDIUM_ENEMY, std::static_pointer_cast<Prototype>(mediumEnemyPrototype) 
		);

		// Medium Enemy Fast
		std::shared_ptr<Enemy> clonedMediumEnemy = std::static_pointer_cast<Enemy>(mediumEnemyPrototype->clone());
		std::shared_ptr<FastEnemy> fastNormalEnemyPrototype = std::make_shared<FastEnemy>(clonedMediumEnemy);

		PrototypeRegistry::getInstance()->addPrototype(
			Prototype_Type::MEDIUM_ENEMY_FAST, std::static_pointer_cast<Prototype>(fastNormalEnemyPrototype)
		);
	}

	// Large Enemy
	{
		// Large Enemy
		std::shared_ptr<TextureType> largeEnemyTexture = std::make_shared<TextureType>(Prototype_Type::LARGE_ENEMY);
		std::shared_ptr<EnemyType> largeEnemyPrototype = std::make_shared<EnemyType>(Prototype_Type::LARGE_ENEMY, 
			largeEnemyTexture, SDL_Point{ 112, 112 }, 10, 2.0F, 30, 37, 7);
		PrototypeRegistry::getInstance()->addPrototype(
			Prototype_Type::LARGE_ENEMY, std::static_pointer_cast<Prototype>(largeEnemyPrototype)
		);

		// Large Enemy Fast
		std::shared_ptr<Enemy> clonedLargeEnemy = std::static_pointer_cast<Enemy>(largeEnemyPrototype->clone());
		std::shared_ptr<FastEnemy> fastLargeEnemyPrototype = std::make_shared<FastEnemy>(clonedLargeEnemy);

		PrototypeRegistry::getInstance()->addPrototype(
			Prototype_Type::LARGE_ENEMY_FAST, std::static_pointer_cast<Prototype>(fastLargeEnemyPrototype)
		);
	}
}


void Game::initMiniMap() {
	Minimap::getInstance()->initMinimap();
}

void Game::initBars() {
	WaveManager::getInstance()->initCountdownBar();
}

void Game::initGameProgress() {
	gameProgress = std::make_unique<GameProgress>();
}

Game* Game::getInstance() {
	static Game instance;
	return &instance;
}

void Game::clearAllPlayers() {
	Player::playerCounter = 1;
	InvokerPlaying::getInstance()->players.clear();
}

void Game::addPlayer() {
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
	static auto moveLeftCommand = std::make_shared<MoveLeftCommand>();
	static auto moveUpCommand = std::make_shared<MoveUpCommand>();
	static auto moveRightCommand = std::make_shared<MoveRightCommand>();
	static auto moveDownCommand = std::make_shared<MoveDownCommand>();

	static auto keyUpMoveLeftCommand = std::make_shared<KeyUpMoveLeftCommand>();
	static auto keyUpMoveUpCommand = std::make_shared<KeyUpMoveUpCommand>();
	static auto keyUpMoveRightCommand = std::make_shared<KeyUpMoveRightCommand>();
	static auto keyUpMoveDownCommand = std::make_shared<KeyUpMoveDownCommand>();

	static auto faceLeftCommand = std::make_shared<FaceLeftCommand>();
	static auto faceUpLeftCommand = std::make_shared<FaceUpLeftCommand>();
	static auto faceUpCommand = std::make_shared<FaceUpCommand>();
	static auto faceUpRightCommand = std::make_shared<FaceUpRightCommand>();
	static 	auto faceRightCommand = std::make_shared<FaceRightCommand>();
	static auto faceDownRightCommand = std::make_shared<FaceDownRightCommand>();
	static auto faceDownCommand = std::make_shared<FaceDownCommand>();
	static auto faceDownLeftCommand = std::make_shared<FaceDownLeftCommand>();

	static 	auto sprintCommand = std::make_shared<SprintCommand>();
	static auto removeSprintCommand = std::make_shared<RemoveSprintCommand>();

	static auto fireCommand = std::make_shared<FireCommand>();
	static auto unfireCommand = std::make_shared<UnfireCommand>();

	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::moveLeft, moveLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::moveUp, moveUpCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::moveRight, moveRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::moveDown, moveDownCommand, player1);

	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::faceLeft, faceLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::faceUpLeft, faceUpLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::faceUp, faceUpCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::faceUpRight, faceUpRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::faceRight, faceRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::faceDownRight, faceDownRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::faceDown, faceDownCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::faceDownLeft, faceDownLeftCommand, player1);

	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::keyUpMoveLeft, keyUpMoveLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::keyUpMoveUp, keyUpMoveUpCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::keyUpMoveRight, keyUpMoveRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::keyUpMoveDown, keyUpMoveDownCommand, player1);

	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::sprint, sprintCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::unsprint, removeSprintCommand, player1);

	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::fire, fireCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(Command_Actions::unfire, unfireCommand, player1);
}

void Game::setState(std::unique_ptr<GameState> state) {
	Menu::getInstance()->resetFlags();
	gameState = std::move(state);
}

void Game::startGame() {
	clearAllPlayers();
	addPlayer();

	WaveManager::getInstance()->resetGame();
	Bullet::bullets.clear();

	GameSound::getInstance()->playMusic();
}

void Game::resetProgress() {
	strncpy_s(gameProgress->playerName, sizeof(gameProgress->playerName), Player::staticStringPlayerName.c_str(), _TRUNCATE);
	gameProgress->waveCount = 0;
	gameProgress->score = 0;

	GameProgressManager::getInstance()->saveProgress(*gameProgress);
}

void Game::loadProgress() {
    GameProgressManager::getInstance()->loadProgress(*gameProgress);

    Player::staticStringPlayerName = gameProgress->playerName;
    Player::staticScore = gameProgress->score;
	Player::playerScoreLoadedFromFile = true;
    WaveManager::getInstance()->setWaveCount(gameProgress->waveCount);
}


void Game::saveProgress() {
	strncpy_s(gameProgress->playerName, sizeof(gameProgress->playerName), Player::staticStringPlayerName.c_str(), _TRUNCATE);
	gameProgress->playerName[sizeof(gameProgress->playerName) - 1] = '\0';
	gameProgress->waveCount = WaveManager::getInstance()->getWaveCount();
	gameProgress->score = Player::staticScore;

	GameProgressManager::getInstance()->saveProgress(*gameProgress);
}

void Game::initAll() {
	initSDLSubsystems();
	initWindowCreation();
	initRendererCreation();
	initSDL_image();
	initSDL_ttf();
	initFonts();
	initGameSound();
	setRunningToTrue();
	initMenu();
	initSelector();
	initBackground();
	initPlayerProfile();
	initPlayer();
	initBullet();
	initEnemy();
	initMiniMap();
	initBars();
	initGameProgress();
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