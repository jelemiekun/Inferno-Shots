#include "Selector.h"
#include "Game.h"
#include "AppInfo.h"
#include <iostream>
#include <SDL_image.h>

Selector::Selector() {}

Selector* Selector::getInstance() {
	static Selector instance;
	return &instance;
}

void Selector::init() {
	SDL_Texture* rawTexture = IMG_LoadTexture(Game::getInstance()->getRenderer(), PATH);

	if (!rawTexture) {
		std::cerr << "Failed to create texture from file " << PATH << ": " << SDL_GetError() << '\n';
		return;
	}

	std::cout << "Texture loaded from path: " << PATH << '\n';
	mTexture.reset(rawTexture);

	SDL_QueryTexture(mTexture.get(), nullptr, nullptr, &dimension.x, &dimension.y);
}

void Selector::update(int distance, int y) {
	midDistance = distance;
	yDistance = y;

	leftSelector = {
		(SCREEN_WIDTH / 2) - (dimension.x / 2) - midDistance,
		yDistance,
		dimension.x / 2 + SIZE_ADDER,
		dimension.y + SIZE_ADDER
	};

	rightSelector = {
		(SCREEN_WIDTH / 2) - (dimension.x / 2) + midDistance,
		yDistance,
		dimension.x / 2 + SIZE_ADDER,
		dimension.y + SIZE_ADDER
	};
}

void Selector::render() {
	SDL_Renderer* renderer = Game::getInstance()->getRenderer();

	SDL_RenderCopy(renderer, mTexture.get(), nullptr, &leftSelector);
	SDL_RenderCopyEx(renderer, mTexture.get(), nullptr, &rightSelector, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
}