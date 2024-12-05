#pragma once
#include <SDL.h>

class Bar {
private:
	SDL_Rect mDstRect;
	SDL_Rect sizeRect;
	SDL_Texture* mTexture;
	SDL_Color mColor;
	float mCurrentAmount;
	float mMaxAmount;
	int mBorderThick;

private:
	void initTexture();
	float getPercentageOfCurrentAmount();
	void calculateSizeRect();
	void renderBorder(SDL_Renderer*& renderer);

public:
	Bar();
	~Bar();

	void setDstRect(SDL_Rect copyDst);
	void setBorderThick(int borderThick);
	void setMaxAmount(float maxAmount);
	void setProgressBarColor(SDL_Color color);

	void update(float currentAmount);
	void render();
};

