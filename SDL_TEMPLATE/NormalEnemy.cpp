#include "NormalEnemy.h"
#include "TextureType.h"
#include "InvokerPlaying.h"
#include "Background.h"
#include "Game.h"
#include <cmath>

constexpr static SDL_Point NORMAL_ENEMY_DIMENSION = { 30, 30 };

constexpr static float NORMAL_ENEMY_SPED = 10.0F;

NormalEnemy::NormalEnemy(std::shared_ptr<TextureType> type) : 
	textureType(type),
	position(std::make_unique<SDL_Point>()),
	movementSpeed(std::make_unique<float>(NORMAL_ENEMY_SPED)),
	directionX(std::make_unique<float>(0.0F)),
	directionY(std::make_unique<float>(0.0F)),
	dead(std::make_unique<bool>(false)) {}

NormalEnemy::NormalEnemy(const NormalEnemy& other)
	: textureType(other.textureType),
	position(std::make_unique<SDL_Point>()),
	movementSpeed(std::make_unique<float>(*other.movementSpeed)),
	directionX(std::make_unique<float>()),
	directionY(std::make_unique<float>()),
	dead(std::make_unique<bool>(false)) {
}

std::shared_ptr<Player> NormalEnemy::getNearestPlayer() {

	std::shared_ptr<Player> nearestPlayer;
	float nearestDistance = 999999.0f;

	for (auto& player : InvokerPlaying::getInstance()->players) {
		float currentDistance = (
			(player.second->position->x - position->x) * (player.second->position->x - position->x) +
			(player.second->position->y - position->y) * (player.second->position->y - position->y)
		);

		if (currentDistance < nearestDistance) {
			nearestPlayer = player.second;
		}
	}

	return nearestPlayer;
}

void NormalEnemy::calculateNormalizedLength(std::shared_ptr<Player> nearestPlayer) {
	float dx = nearestPlayer->position->x - position->x;
	float dy = nearestPlayer->position->y - position->y;

	float distance = sqrt(dx * dx + dy * dy);

	*directionX = dx / distance;
	*directionY = dy / distance;
}

void NormalEnemy::move() {
	position->x += *directionX * *movementSpeed;
	position->y += *directionY * *movementSpeed;
}

void NormalEnemy::update() {
	std::shared_ptr<Player> nearestPlayer = getNearestPlayer();
	calculateNormalizedLength(nearestPlayer);
}

void NormalEnemy::render() const {
	SDL_Rect dstRect = { position->x, position->y, NORMAL_ENEMY_DIMENSION.x, NORMAL_ENEMY_DIMENSION.y };

	SDL_SetRenderTarget(Game::getInstance()->getRenderer(), Background::getInstance()->background);
	SDL_RenderCopy(Game::getInstance()->getRenderer(), textureType->texture, nullptr, &dstRect);
	SDL_SetRenderTarget(Game::getInstance()->getRenderer(), nullptr);
}

const bool& NormalEnemy::isDead() const {
	return *dead;
}


std::shared_ptr<Prototype> NormalEnemy::clone() const {
	return std::make_shared<NormalEnemy>(*this);
}