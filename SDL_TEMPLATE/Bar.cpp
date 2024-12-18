#include "Bar.h"
#include "Game.h"
#include "BorderManager.h"

Bar::Bar() : mTexture(nullptr) {}

Bar::~Bar() {
	SDL_DestroyTexture(mTexture);
}

void Bar::initTexture() {
    mTexture = SDL_CreateTexture(
        Game::getInstance()->getRenderer(),
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        mDstRect.w,
        mDstRect.h
    );
}

float Bar::getPercentageOfCurrentAmount() {
	return static_cast<float>(mCurrentAmount) / mMaxAmount;
}

void Bar::calculateSizeRect() {
	float percentage = getPercentageOfCurrentAmount();
	sizeRect = { 0, 0, static_cast<int>(mDstRect.w * percentage), mDstRect.h };
}

void Bar::renderBorder(SDL_Renderer*& renderer) {
	constexpr static SDL_Color borderColor = { 0, 0, 0, 255};
	Border::bRenderBorder(renderer, mDstRect, mBorderThick, borderColor);
}

void Bar::setDstRect(SDL_Rect copyDst) {
	mDstRect = copyDst;
	initTexture();
}

void Bar::setBorderThick(int borderThick) {
	mBorderThick = borderThick;
}

void Bar::setMaxAmount(float maxAmount) {
	mMaxAmount = maxAmount;
}

void Bar::setProgressBarColor(SDL_Color color) {
	mColor = color;
}

void Bar::update(float currentAmount) {
	if (currentAmount > mMaxAmount) mCurrentAmount = mMaxAmount;
	else mCurrentAmount = currentAmount;

	calculateSizeRect();
}

void Bar::render() {
	SDL_Renderer* renderer = Game::getInstance()->getRenderer();

	SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, mTexture);
	SDL_SetRenderDrawColor(renderer, 110, 110, 110, 120);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
	
	SDL_RenderFillRect(renderer, &sizeRect);

	SDL_SetRenderTarget(renderer, nullptr);
	SDL_RenderCopy(renderer, mTexture, nullptr, &mDstRect);
	renderBorder(renderer);
}