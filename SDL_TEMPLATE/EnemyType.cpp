#include "EnemyType.h"
#include "TextureType.h"
#include "InvokerPlaying.h"
#include "GameEnums.h"
#include "Background.h"
#include "Game.h"
#include "Player.h"
#include "WaveManager.h"
#include <cmath>
#include <random>

EnemyType::EnemyType(std::shared_ptr<TextureType> type, SDL_Point dimension, int healthCount,
	float speed, int damage, int score, int minimapSize) :
	textureType(type),
	dimension(std::make_unique<SDL_Point>(dimension)),
	healthCount(std::make_unique<int>(healthCount)),
	damage(std::make_unique<int>(damage)),
	score(std::make_unique<int>(score)),
	position(std::make_unique<SDL_Point>()),
	movementSpeed(std::make_unique<float>(speed)),
	directionX(std::make_unique<float>(0.0F)),
	directionY(std::make_unique<float>(0.0F)),
	dead(std::make_unique<bool>(false)),
	inflicted(std::make_unique<bool>(false)),
	minimapSize(std::make_unique<int>(minimapSize)) {}

EnemyType::EnemyType(const EnemyType& other)
	: textureType(other.textureType),
	dimension(std::make_unique<SDL_Point>(*other.dimension)),
	healthCount(std::make_unique<int>(*other.healthCount)),
	damage(std::make_unique<int>(*other.damage)),
	score(std::make_unique<int>(*other.score)),
	position(std::make_unique<SDL_Point>(*other.position)),
	movementSpeed(std::make_unique<float>(*other.movementSpeed)),
	directionX(std::make_unique<float>(*other.directionX)),
	directionY(std::make_unique<float>(*other.directionY)),
	dead(std::make_unique<bool>(*other.dead)),
	inflicted(std::make_unique<bool>(*other.inflicted)) ,
	minimapSize(std::make_unique<int>(*other.minimapSize)){}

std::shared_ptr<Player> EnemyType::getNearestPlayer() {
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


void EnemyType::calculateNormalizedLength(std::shared_ptr<Player> nearestPlayer) {
	float dx = static_cast<float>(nearestPlayer->position->x + (Player::PLAYER_DIMENSION.x / 2)) - position->x + Background::getInstance()->srcRect->x;
	float dy = static_cast<float>(nearestPlayer->position->y + (Player::PLAYER_DIMENSION.y / 2)) - position->y + Background::getInstance()->srcRect->y;

	float distance = sqrt(dx * dx + dy * dy);

	*directionX = static_cast<float>(dx) / distance;
	*directionY = static_cast<float>(dy) / distance;
}

void EnemyType::move() {
	position->x += static_cast<int>(*directionX * *movementSpeed);
	position->y += static_cast<int>(*directionY * *movementSpeed);
}

void EnemyType::initPos() {
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

int EnemyType::getEnemyScore() {
	return *score;
}

void EnemyType::undoMove() {
	position->x -= static_cast<int>(*directionX * *movementSpeed);
	position->y -= static_cast<int>(*directionY * *movementSpeed);
}

void EnemyType::checkCollision() {
	for (const auto& otherEnemy : WaveManager::getInstance()->getEnemies()) {
		EnemyType* EnemyTypePtr = dynamic_cast<EnemyType*>(otherEnemy.get());
		if (!EnemyTypePtr || otherEnemy == shared_from_this()) {
			continue;
		}

		SDL_Point pos1 = *position;
		SDL_Point pos2 = *EnemyTypePtr->position;

		if (pos1.x < pos2.x + dimension->x &&
			pos1.x + dimension->x > pos2.x &&
			pos1.y < pos2.y + dimension->y &&
			pos1.y + dimension->y > pos2.y) {
			undoMove();
			undoMove();
			undoMove();
		}
	}

	if (position->x < static_cast<float>(BORDER_ALLOWANCE))
		position->x = static_cast<int>(static_cast<float>(BORDER_ALLOWANCE));
	if (position->x + dimension->x >
		Background::getInstance()->getDimension().x - static_cast<float>(BORDER_ALLOWANCE))
		position->x = static_cast<int>(Background::getInstance()->getDimension().x - 
			dimension->x - static_cast<float>(BORDER_ALLOWANCE));
	if (position->y < static_cast<float>(BORDER_ALLOWANCE))
		position->y = static_cast<int>(static_cast<float>(BORDER_ALLOWANCE));
	if (position->y + dimension->y >
		Background::getInstance()->getDimension().y - static_cast<float>(BORDER_ALLOWANCE))
		position->y = static_cast<int>(Background::getInstance()->getDimension().y - 
			dimension->y - static_cast<float>(BORDER_ALLOWANCE));
}



void EnemyType::update() {
	std::shared_ptr<Player> nearestPlayer = getNearestPlayer();
	if (nearestPlayer) {
		calculateNormalizedLength(nearestPlayer);
		move();
	}
}

void EnemyType::render() const {
	SDL_Rect dstRect = { 
		position->x - Background::getInstance()->srcRect->x,
		position->y - Background::getInstance()->srcRect->y,
		dimension->x,
		dimension->y
	};
	
	SDL_SetRenderTarget(Game::getInstance()->getRenderer(), Background::getInstance()->background);
	SDL_RenderCopy(Game::getInstance()->getRenderer(), textureType->texture, nullptr, &dstRect);
	SDL_SetRenderTarget(Game::getInstance()->getRenderer(), nullptr);
}

const bool& EnemyType::isDead() const {
	return *dead;
}

void EnemyType::setDead() {
	*dead = true;
}

void EnemyType::decreaseHealth() {
	--*healthCount;
	if (*healthCount == 0)
		setDead();
}

std::shared_ptr<Prototype> EnemyType::clone() const {
	return std::make_shared<EnemyType>(*this);
}

const SDL_Point& EnemyType::getPosition() const {
	return *position.get();
}

int EnemyType::getMinimapPixelSize() {
	return *minimapSize;
}

const SDL_Point& EnemyType::getDimension() const {
	return *dimension;
}

const int EnemyType::getDamage() const {
	return *damage;
}
