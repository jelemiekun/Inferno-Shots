#pragma once
#include <SDL.h>
#include <iostream>

using Dimension = SDL_Point;

class Background {
private:
	Background();

private:
	Dimension* dimension;

public:
	SDL_Texture* background;
	SDL_Rect* srcRect;

private:
	void checkIfBackgroundIsLoaded();
	void setDimension();
	void setSrcRect();

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

