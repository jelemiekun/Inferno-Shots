#pragma once
#include <SDL.h>
#include <memory>
#include <SDL_ttf.h>

class GameState;

class Game {

private:
	static Game* game;

	std::unique_ptr<GameState> gameState;

protected:
	Game();

public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

private:
	SDL_Event gEvent;

public:
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	bool running;

	TTF_Font* gFont;

private:
	void initSDLSubsystems();
	void initWindowCreation();
	void initRendererCreation();
	void initSDL_image();
	void initSDL_ttf();
	void initGFont();
	void setRunningToTrue();
	void setRunningToFalse();

public:
	static Game* getInstance();

	void init();
	void input();
	void update();
	void render();

	const SDL_Renderer* getRenderer() const;
	const bool& isRunning() const;
	const SDL_Event& getEvent() const;
};

