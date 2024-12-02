#include "Background.h"
#include "Game.h"
#include "SDL_image.h"
#include "AppInfo.h"

Background::Background() : background(nullptr), dimension(nullptr), srcRect(nullptr) {}

void Background::checkIfBackgroundIsLoaded() {
	if (background) {
		std::cout << "Background loaded." << '\n';
		setDimension();
		setDstRect();
	} else {
		std::cout << "Failed to load background: " << IMG_GetError() << '\n';
	}
}

void Background::setDimension() {
	dimension = new Dimension;

	SDL_QueryTexture(background, nullptr, nullptr, &dimension->x, &dimension->y);
}

void Background::setDstRect() {
	srcRect = new SDL_Rect;
	srcRect->w = SCREEN_WIDTH;
	srcRect->h = SCREEN_HEIGHT;
	srcRect->x = (SCREEN_WIDTH / 2);
	srcRect->y = (SCREEN_HEIGHT / 2);
}

Background* Background::getInstance() {
	static Background instance;
	return &instance;
}

void Background::init() {
	background = IMG_LoadTexture(Game::getInstance()->getRenderer(), BACKGROUND_PATH.c_str());
	checkIfBackgroundIsLoaded();
}

void Background::render() {
	SDL_RenderCopy(Game::getInstance()->getRenderer(), background, srcRect, nullptr);
}

bool Background::isRightEdge() {
	return srcRect->x + srcRect->w >= dimension->x;
}

bool Background::isLeftEdge() {
	return srcRect->x <= 0;
}

bool Background::isUpEdge() {
	return srcRect->y <= 0;
}

bool Background::isDownEdge() {
	return srcRect->y + srcRect->h >= dimension->y;
}
