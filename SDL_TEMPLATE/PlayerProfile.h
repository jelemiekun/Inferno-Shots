#pragma once
#include <SDL.h>

class Bar;

class PlayerProfile {
private:
	constexpr static SDL_Color HEALTH_COLOR = { 0, 230, 0, 255 };
	constexpr static int BORDER_THICK = 2;
	constexpr static int Y_ALLOWANCE = 15;
	constexpr static SDL_Point TEXTURE_DIMENSION = { 235, 80 };
	constexpr static int X_ALLOWANCE = 15;
	SDL_Color SPRINT_COLOR;
	static SDL_Texture* mTextureProfiles;

private:
	int playerID;
	SDL_Texture* mTexture;
	SDL_Rect mDstRectTexture;
	SDL_Rect mSrcRectProfile;
	SDL_Rect mDstRectProfile;
	Bar* healthBar;
	Bar* sprintBar;

private:
	void initPlayerID(int playerID);
	void initMTexture();
	void initMDstRectTexture();
	void initMDstRectProfile();
	void initMSrcRectProfile();
	void initSprintColor();
	void initHealthBar(int maxHealth);
	void initSprintBar(int maxSprint);

public:
	static void loadPlayerProfiles();

public:
	PlayerProfile();
	~PlayerProfile();

	void init(int playerID, int maxHealth, int maxSprint);
	void update(int healthAmount, int sprintAmount);
	void render() const;
};

