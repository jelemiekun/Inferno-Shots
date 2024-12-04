#include "NormalEnemy.h"
#include "TextureType.h"
#include "InvokerPlaying.h"
#include "GameEnums.h"
#include "Background.h"
#include "Game.h"
#include "Player.h"
#include "Background.h"
#include <cmath>
#include <random>

constexpr static SDL_Point NORMAL_ENEMY_DIMENSION = { 30, 30 };

constexpr static float NORMAL_ENEMY_SPED = 3.0F;

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
	float nearestDistance = std::numeric_limits<float>::max();

	for (auto& player : InvokerPlaying::getInstance()->players) {
		float currentDistance = (
			(player.second->position->x - position->x) * (player.second->position->x - position->x) +
			(player.second->position->y - position->y) * (player.second->position->y - position->y)
			);

		if (currentDistance < nearestDistance) {
			nearestDistance = currentDistance;
			nearestPlayer = player.second;
		}
	}

	return nearestPlayer;
}


void NormalEnemy::calculateNormalizedLength(std::shared_ptr<Player> nearestPlayer) {
	// Get the player position adjusted for background scrolling
	float playerX = nearestPlayer->position->x + Background::getInstance()->srcRect->x;
	float playerY = nearestPlayer->position->y + Background::getInstance()->srcRect->y;

	// Calculate the direction vector from the enemy to the player
	float dx = playerX - position->x;
	float dy = playerY - position->y;

	// Normalize the direction vector
	float distance = sqrt(dx * dx + dy * dy);
	if (distance > 0) { // Avoid division by zero
		*directionX = dx / distance;
		*directionY = dy / distance;
	}
}


void NormalEnemy::move() {
	// Move the enemy in the direction of the player with its speed
	position->x += *directionX * *movementSpeed;
	position->y += *directionY * *movementSpeed;
}


void NormalEnemy::initPos() {
	static std::random_device dev;
	static std::mt19937 rng(dev());

	std::uniform_int_distribution<std::mt19937::result_type> distX(
		BORDER_ALLOWANCE,
		Background::getInstance()->getDimension().x - BORDER_ALLOWANCE - textureType->dimension.x
	);

	std::uniform_int_distribution<std::mt19937::result_type> distY(
		BORDER_ALLOWANCE,
		Background::getInstance()->getDimension().y - BORDER_ALLOWANCE - textureType->dimension.y
	);

	position->x = distX(rng);
	position->y = distY(rng);
}


void NormalEnemy::update() {
	std::shared_ptr<Player> nearestPlayer = getNearestPlayer();
	if (nearestPlayer) {
		// Calculate the direction the enemy should move
		calculateNormalizedLength(nearestPlayer);
		// Move the enemy based on that direction
		move();
	}
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