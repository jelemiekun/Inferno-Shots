#include "Bullet.h"
#include "GameEnums.h"
#include "AppInfo.h"
#include "Background.h"
#include "Game.h"
#include "TextureType.h"

std::vector<std::unique_ptr<Bullet>> Bullet::bullets;

Bullet::Bullet(std::shared_ptr<TextureType> texture)
	: textureType(texture),
	remove(std::make_unique<bool>(false)) {
}

Bullet::Bullet(const Bullet& other)
	: textureType(std::make_unique<TextureType>(*other.textureType)),
	remove(std::make_unique<bool>(*other.remove)) {}

Bullet::~Bullet() {}

void Bullet::initPos(SDL_Point pos) {
	position = std::make_unique<SDL_Point>(pos);
}

void Bullet::initDirections(float x, float y) {
	this->directionX = std::make_unique<float>(x);
	this->directionY = std::make_unique<float>(y);
}

void Bullet::initMovementSpeed(float movementSpeed) {
	this->movementSpeed = std::make_unique<float>(movementSpeed);
}

void Bullet::checkCollision() {
	// Check border collision
	if (position->x < 0 || position->x + BULLET_DIMENSION.x > Background::getInstance()->getDimension().x ||
		position->y < 0 || position->y + BULLET_DIMENSION.y > Background::getInstance()->getDimension().y) {
		*remove = true;
	}

	// Check collision per zombie
}

void Bullet::update() {
	position->x += (*directionX * *movementSpeed);
	position->y += (*directionY * *movementSpeed);

	checkCollision();
}

void Bullet::render() {
	SDL_Rect dstRect = { position->x, position->y, BULLET_DIMENSION.x ,BULLET_DIMENSION.y };
	std::cout << position->x << ", " << position->y << ", " << BULLET_DIMENSION.x << ", " << BULLET_DIMENSION.y << '\n';
	SDL_RenderCopy(Game::getInstance()->getRenderer(), textureType->texture, nullptr, &dstRect);
}

std::shared_ptr<Prototype> Bullet::clone() const {
	return std::make_shared<Bullet>(*this);
}