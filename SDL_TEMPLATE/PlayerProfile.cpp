#include "PlayerProfile.h"
#include "Bar.h"
#include "Game.h"
#include "SDL_image.h"
#include "BorderManager.h"
#include <iostream>

constexpr const static char* PATH = "assets/images/players_profile.png";

SDL_Texture* PlayerProfile::mTextureProfiles = nullptr;

void PlayerProfile::loadPlayerProfiles() {
	SDL_Surface* surface = IMG_Load(PATH);

	if (surface) {
		mTextureProfiles = SDL_CreateTextureFromSurface(
			Game::getInstance()->getRenderer(),
			surface
			);

		if (mTextureProfiles) std::cout << "Text with path " << PATH << " loaded." << '\n';
		else std::cout << "Failed to create texture from surface of player profiles" << SDL_GetError() << '\n';
	} else {
		std::cout << "Failed to load player profiles: " << IMG_GetError() << '\n';
	}

	SDL_FreeSurface(surface);
}

PlayerProfile::PlayerProfile() :
	playerID(0),
	mTexture(nullptr), 
	healthBar(nullptr),
	sprintBar(nullptr) {}

PlayerProfile::~PlayerProfile() {
	SDL_DestroyTexture(mTexture);
	delete healthBar;
	delete sprintBar;
}

void PlayerProfile::initPlayerID(int playerID) {
	this->playerID = playerID;
}

void PlayerProfile::initMTexture() {
	mTexture = SDL_CreateTexture(
		Game::getInstance()->getRenderer(),
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		100, //TODO
		30
	);
}

void PlayerProfile::initMDstRectTexture() {
	int count = playerID - 1;

	switch (playerID) {
	case 1:
		mDstRectTexture = { 
			(X_ALLOWANCE * playerID) + (TEXTURE_DIMENSION.x * count),
			Y_ALLOWANCE, 
			TEXTURE_DIMENSION.x, 
			TEXTURE_DIMENSION.y
		};
		break;
	case 2:
		mDstRectTexture = { 
			(X_ALLOWANCE * playerID) + (TEXTURE_DIMENSION.x * count), 
			Y_ALLOWANCE, 
			TEXTURE_DIMENSION.x, 
			TEXTURE_DIMENSION.y 
		};
		break;
	case 3:
		mDstRectTexture = { 
			(X_ALLOWANCE * playerID) + (TEXTURE_DIMENSION.x * count), 
			Y_ALLOWANCE, 
			TEXTURE_DIMENSION.x, 
			TEXTURE_DIMENSION.y 
		};
		break;
	case 4:
		mDstRectTexture = { 
			(X_ALLOWANCE * playerID) + (TEXTURE_DIMENSION.x * count), 
			Y_ALLOWANCE, 
			TEXTURE_DIMENSION.x, 
			TEXTURE_DIMENSION.y 
		};
		break;
	default: mDstRectTexture = { 0, 0, 0, 0 }; break;
	}
}

void PlayerProfile::initMSrcRectProfile() {
	int pos = playerID - 1;

	int profileW = 0;
	int profileH = 0;

	SDL_QueryTexture(mTextureProfiles, nullptr, nullptr, &profileW, &profileH);

	mSrcRectProfile = {
		(profileW / 5) * pos,
		0,
		(profileW / 5),
		profileH
	};
}

void PlayerProfile::initMDstRectProfile() {
	mDstRectProfile = {
		0,
		0,
		35,
		30,
	};
}

void PlayerProfile::initSprintColor() {
	switch (playerID) {
	case 1: SPRINT_COLOR = { 255, 163, 234, 255 };	 break;
	case 2: SPRINT_COLOR = { 157, 171, 244, 255 }; break;
	case 3: SPRINT_COLOR = { 183, 244, 197, 255 }; break;
	case 4: SPRINT_COLOR = { 236, 244, 183, 255 }; break;
	default: SPRINT_COLOR = { 0, 0, 0, 255 }; break;
	}
}

void PlayerProfile::initHealthBar(int maxHealth) {
	SDL_Rect healthBarRect = { (105 * playerID), 55, 137, 10 };
	healthBar = new Bar;
	healthBar->setDstRect(healthBarRect);
	healthBar->setBorderThick(BORDER_THICK);
	healthBar->setMaxAmount(maxHealth);
	healthBar->setProgressBarColor(HEALTH_COLOR);
}

void PlayerProfile::initSprintBar(int maxSprint) {
	SDL_Rect sprintBarRect = { (105 * playerID), 75, 137, 10 };
	sprintBar = new Bar;
	sprintBar->setDstRect(sprintBarRect);
	sprintBar->setBorderThick(BORDER_THICK);
	sprintBar->setMaxAmount(maxSprint);
	sprintBar->setProgressBarColor(SPRINT_COLOR);
}

void PlayerProfile::init(int playerID, int maxHealth, int maxSprint) {
	initPlayerID(playerID);
	initMTexture();
	initMDstRectTexture();
	initMDstRectProfile();
	initMSrcRectProfile();
	initSprintColor();
	initHealthBar(maxHealth);
	initSprintBar(maxSprint);
}

void PlayerProfile::update(int healthAmount, int sprintAmount) {
	healthBar->update(healthAmount);
	sprintBar->update(sprintAmount);
}

void PlayerProfile::render() const {
	SDL_Renderer* renderer = Game::getInstance()->getRenderer();

	SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, mTexture);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, mTextureProfiles, &mSrcRectProfile, &mDstRectProfile);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, mDstRectProfile.w, 0, mDstRectProfile.w - 1, mDstRectProfile.h);

	SDL_SetRenderTarget(renderer, nullptr);
	SDL_RenderCopy(renderer, mTexture, nullptr, &mDstRectTexture);

	healthBar->render();
	sprintBar->render();

	Border::bRenderBorder(renderer, mDstRectTexture, BORDER_THICK, { 0, 0, 0, 255 });
}