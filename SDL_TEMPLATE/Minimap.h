#pragma once
#include <vector>
#include <SDL.h>

class Minimap {
private:
	Minimap();

public:
	Minimap(const Minimap&) = delete;
	Minimap& operator=(const Minimap&) = delete;
	Minimap(Minimap&&) = delete;
	Minimap& operator=(Minimap&&) = delete;

public:
	static Minimap* getInstance();

private:
	SDL_Texture* minimapTexture;
	SDL_Rect dstRectMinimap;
	std::vector<SDL_Rect> players;
	std::vector<SDL_Rect> bullets;
	std::vector<SDL_Rect> enemies;
	float scaleX;
	float scaleY;

private:
	void clearVectors();
	void initMinimapTexture();
	void initScalars();
	void renderBorder(SDL_Renderer*& renderer);

public:
	void initMinimap();
	void update();
	void render();
};

