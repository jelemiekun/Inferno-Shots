#include "Minimap.h"
#include "Game.h"
#include "AppInfo.h"
#include "Background.h"
#include "WaveManager.h"
#include "InvokerPlaying.h"
#include "Bullet.h"
#include "NormalEnemy.h"
#include "Enemy.h"

Minimap::Minimap() {}

Minimap* Minimap::getInstance() {
	static Minimap instance;
	return &instance;
}

void Minimap::clearVectors() {
	players.clear();
	bullets.clear();
	enemies.clear();
}

void Minimap::initMinimapTexture() {
	constexpr int ALLOWANCE = 15;
	constexpr int DIMENSION = 150;

	minimapTexture = SDL_CreateTexture(
		Game::getInstance()->getRenderer(),
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		DIMENSION,
		DIMENSION
	);

	dstRectMinimap.w = DIMENSION;
	dstRectMinimap.h = DIMENSION;
	dstRectMinimap.x = SCREEN_WIDTH - DIMENSION - ALLOWANCE;
	dstRectMinimap.y = ALLOWANCE;
}

void Minimap::initScalars() {
	scaleX = static_cast<float>(dstRectMinimap.w) / Background::getInstance()->getDimension().x;
	scaleY = static_cast<float>(dstRectMinimap.h) / Background::getInstance()->getDimension().y;
}

void Minimap::initMinimap() {
	initMinimapTexture();
	initScalars();
}

void Minimap::renderBorder(SDL_Renderer *& renderer) {
	constexpr static int BORDER_THICK = 2;
	for (int borderCount = 0; borderCount < BORDER_THICK; borderCount++) {
		SDL_Rect border = {
			dstRectMinimap.x - borderCount,
			dstRectMinimap.y - borderCount,
			dstRectMinimap.w + (borderCount * 2),
			dstRectMinimap.h + (borderCount * 2)
		};

		SDL_SetRenderDrawColor(renderer, 10, 10, 10, 120);
		SDL_RenderDrawRect(renderer, &border);
	}
}

void Minimap::update() {
	constexpr static SDL_Point PLAYER_DIMENSION = { 4, 4 };
	constexpr static SDL_Point BULLET_DIMENSION = { 2, 2 };
	constexpr static SDL_Point NORMAL_ENEMY_DIMENSION = { 4, 4 };

	clearVectors();

	for (const auto& player : InvokerPlaying::getInstance()->players) {
		SDL_Rect playerPos = {
			static_cast<int>((player.second->platformPosition->x - (Player::PLAYER_DIMENSION.x / 2)) * scaleX),
			static_cast<int>((player.second->platformPosition->y - (Player::PLAYER_DIMENSION.y / 2)) * scaleY),
			PLAYER_DIMENSION.x,
			PLAYER_DIMENSION.y
		};
		players.push_back(playerPos);
	}

	for (const auto& bullet : Bullet::bullets) {
		SDL_Rect bulletPos = {
			static_cast<int>((bullet->position->x - (BULLET_DIMENSION.x / 2)) * scaleX),
			static_cast<int>((bullet->position->y - (BULLET_DIMENSION.y / 2)) * scaleY),
			BULLET_DIMENSION.x,
			BULLET_DIMENSION.y
		};
		bullets.push_back(bulletPos);
	}

	for (const auto& enemy : WaveManager::getInstance()->getEnemies()) {
		SDL_Rect enemyPos = { 0, 0, 0, 0 };

		if (dynamic_cast<NormalEnemy*>(enemy.get())) {
			enemyPos = {
				static_cast<int>((enemy->getPosition().x - (NORMAL_ENEMY_DIMENSION.x / 2)) * scaleX),
				static_cast<int>((enemy->getPosition().y - (NORMAL_ENEMY_DIMENSION.y / 2)) * scaleY),
				NORMAL_ENEMY_DIMENSION.x,
				NORMAL_ENEMY_DIMENSION.y
			};	
		}

		if (enemyPos.w != 0 && enemyPos.h != 0) enemies.push_back(enemyPos);
	}
}

void Minimap::render() {
	SDL_Renderer* renderer = Game::getInstance()->getRenderer();

	SDL_SetTextureBlendMode(minimapTexture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, minimapTexture);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 75);
	SDL_RenderClear(renderer);

	for (const auto& player : players) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 170);
		SDL_RenderFillRect(renderer, &player);
	}

	for (const auto& bullet : bullets) {
		SDL_SetRenderDrawColor(renderer, 70, 70, 70, 150);
		SDL_RenderFillRect(renderer, &bullet);
	}

	for (const auto& enemy : enemies) {
		SDL_SetRenderDrawColor(renderer, 150, 50, 50, 120);
		SDL_RenderFillRect(renderer, &enemy);
	}

	SDL_SetRenderTarget(renderer, nullptr);
	renderBorder(renderer);
	SDL_RenderCopy(renderer, minimapTexture, nullptr, &dstRectMinimap);
}