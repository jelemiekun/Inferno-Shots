#include "NormalEnemy.h"
#include "TextureType.h"
#include "InvokerPlaying.h"
#include "GameEnums.h"
#include "Background.h"
#include "Game.h"
#include "Player.h"
#include "WaveManager.h"
#include <cmath>
#include <random>

constexpr static float NORMAL_ENEMY_SPED = 3.0F;

NormalEnemy::NormalEnemy(std::shared_ptr<TextureType> type) : 
	textureType(type),
	position(std::make_unique<SDL_Point>()),
	movementSpeed(std::make_unique<float>(NORMAL_ENEMY_SPED)),
	directionX(std::make_unique<float>(0.0F)),
	directionY(std::make_unique<float>(0.0F)),
	dead(std::make_unique<bool>(false)),
	inflicted(std::make_unique<bool>(false)) {}

NormalEnemy::NormalEnemy(const NormalEnemy& other)
	: textureType(other.textureType),
	position(std::make_unique<SDL_Point>()),
	movementSpeed(std::make_unique<float>(*other.movementSpeed)),
	directionX(std::make_unique<float>()),
	directionY(std::make_unique<float>()),
	dead(std::make_unique<bool>(false)),
	inflicted(std::make_unique<bool>(false)) {
}

std::shared_ptr<Player> NormalEnemy::getNearestPlayer() {
	std::shared_ptr<Player> nearestPlayer;
	float nearestDistance = std::numeric_limits<float>::max();

	for (auto& player : InvokerPlaying::getInstance()->players) {
		float currentDistance = static_cast<float>(
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
	float dx = static_cast<float>(nearestPlayer->position->x + (Player::PLAYER_DIMENSION.x / 2)) - position->x + Background::getInstance()->srcRect->x;
	float dy = static_cast<float>(nearestPlayer->position->y + (Player::PLAYER_DIMENSION.y / 2)) - position->y + Background::getInstance()->srcRect->y;

	float distance = sqrt(dx * dx + dy * dy);

	*directionX = static_cast<float>(dx) / distance;
	*directionY = static_cast<float>(dy) / distance;
}

void NormalEnemy::move() {
	position->x += static_cast<int>(*directionX * *movementSpeed);
	position->y += static_cast<int>(*directionY * *movementSpeed);
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

int NormalEnemy::getEnemyScore() {
	static int NORMAL_ENEMY_SCORE = 3;
	return NORMAL_ENEMY_SCORE;
}

void NormalEnemy::undoMove() {
	position->x -= static_cast<int>(*directionX * *movementSpeed);
	position->y -= static_cast<int>(*directionY * *movementSpeed);
}

void NormalEnemy::checkCollision() {
	for (const auto& otherEnemy : WaveManager::getInstance()->getEnemies()) {
		NormalEnemy* normalEnemyPtr = dynamic_cast<NormalEnemy*>(otherEnemy.get());
		if (!normalEnemyPtr || otherEnemy == shared_from_this()) {
			continue;
		}

		SDL_Point pos1 = *position;
		SDL_Point pos2 = *normalEnemyPtr->position;

		if (pos1.x < pos2.x + NORMAL_ENEMY_DIMENSION.x &&
			pos1.x + NORMAL_ENEMY_DIMENSION.x > pos2.x &&
			pos1.y < pos2.y + NORMAL_ENEMY_DIMENSION.y &&
			pos1.y + NORMAL_ENEMY_DIMENSION.y > pos2.y) {
			undoMove();
			undoMove();
			undoMove();
		}
	}

	if (position->x < static_cast<float>(BORDER_ALLOWANCE))
		position->x = static_cast<int>(static_cast<float>(BORDER_ALLOWANCE));
	if (position->x + NORMAL_ENEMY_DIMENSION.x > 
		Background::getInstance()->getDimension().x - static_cast<float>(BORDER_ALLOWANCE))
		position->x = static_cast<int>(Background::getInstance()->getDimension().x - 
			NORMAL_ENEMY_DIMENSION.x - static_cast<float>(BORDER_ALLOWANCE));
	if (position->y < static_cast<float>(BORDER_ALLOWANCE))
		position->y = static_cast<int>(static_cast<float>(BORDER_ALLOWANCE));
	if (position->y + NORMAL_ENEMY_DIMENSION.y > 
		Background::getInstance()->getDimension().y - static_cast<float>(BORDER_ALLOWANCE))
		position->y = static_cast<int>(Background::getInstance()->getDimension().y - 
			NORMAL_ENEMY_DIMENSION.y - static_cast<float>(BORDER_ALLOWANCE));
}



void NormalEnemy::update() {
	std::shared_ptr<Player> nearestPlayer = getNearestPlayer();
	if (nearestPlayer) {
		calculateNormalizedLength(nearestPlayer);
		move();
	}
}

void NormalEnemy::render() const {
	SDL_Rect dstRect = { 
		position->x - Background::getInstance()->srcRect->x,
		position->y - Background::getInstance()->srcRect->y,
		NORMAL_ENEMY_DIMENSION.x, 
		NORMAL_ENEMY_DIMENSION.y 
	};
	
	SDL_SetRenderTarget(Game::getInstance()->getRenderer(), Background::getInstance()->background);
	SDL_RenderCopy(Game::getInstance()->getRenderer(), textureType->texture, nullptr, &dstRect);
	SDL_SetRenderTarget(Game::getInstance()->getRenderer(), nullptr);
}

const bool& NormalEnemy::isDead() const {
	return *dead;
}

void NormalEnemy::setDead() {
	*dead = true;
}

std::shared_ptr<Prototype> NormalEnemy::clone() const {
	return std::make_shared<NormalEnemy>(*this);
}

const SDL_Point& NormalEnemy::getPosition() const {
	return *position.get();
}
const SDL_Point& NormalEnemy::getDimension() const {
	return NORMAL_ENEMY_DIMENSION;
}

const int NormalEnemy::getDamage() const {
	return NORMAL_ENEMY_DAMAGE;
}
