#pragma once
#include <SDL.h>
#include <iostream>

using Dimension = SDL_Point;

class Background {
private:
	Background();

private:
	const std::string BACKGROUND_PATH = "assets/images/backgroundGame.png";
	Dimension* dimension;

public:
	SDL_Texture* background;
	SDL_Rect* srcRect;

private:
	void checkIfBackgroundIsLoaded();
	void setDimension();
	void setDstRect();

public:
	Background(const Background&) = delete;
	Background& operator=(const Background&) = delete;
	Background(Background&&) = delete;
	Background& operator=(Background&&) = delete;

	static Background* getInstance();

	void init();
	void render();

	bool isRightEdge();
	bool isLeftEdge();
	bool isUpEdge();
	bool isDownEdge();
	const SDL_Point& getDimension() const;
};

