#pragma once
#include <SDL.h>
#include <memory>
#include <SDL_ttf.h>

class GameState;
struct GameProgress;

class Game {

private:
	std::unique_ptr<GameState> gameState;
	std::unique_ptr<GameProgress> gameProgress;

protected:
	Game();

public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	SDL_Event gEvent;

public:
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	bool running;

private:
	void initSDLSubsystems();
	void initWindowCreation();
	void initRendererCreation();
	void initSDL_image();
	void initSDL_ttf();
	void initFonts();
	void setRunningToTrue();
	void initMenu();
	void initSelector();
	void initBackground();
	void initPlayerProfile();
	void initPlayer();
	void initBullet();
	void initEnemy();
	void initMiniMap();
	void initBars();
	void initGameProgress();
	void clearAllPlayers();
	void addPlayer();

public:
	static Game* getInstance();

public:
	void setState(std::unique_ptr<GameState> state);

	void startGame();

	void resetProgress();
	void loadProgress();
	void saveProgress();

	void initAll();
	void input();
	void update();
	void render();

	SDL_Renderer* getRenderer();
	const SDL_Event& getEvent() const;
	const bool& isRunning() const;
	void setRunningToFalse();
};

