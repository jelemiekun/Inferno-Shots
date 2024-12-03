#include "Bullet.h"
#include "GameEnums.h"
#include "AppInfo.h"
#include "Background.h"
#include "Game.h"
#include "TextureType.h"

std::vector<std::unique_ptr<Bullet>> Bullet::bullets;

Bullet::Bullet() : remove(std::make_unique<bool>(false)) {}

Bullet::Bullet(const Bullet& other)
	: remove(std::make_unique<bool>(*other.remove)) {}

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

void Bullet::initTexture(std::shared_ptr<TextureType> textureType) {
	this->textureType = textureType;
}

void Bullet::checkCollision() {
	if (position->x < BORDER_ALLOWANCE * 1.5 ||
		position->x + BULLET_DIMENSION.x > Background::getInstance()->getDimension().x - (BORDER_ALLOWANCE * 1.5) ||
		position->y < BORDER_ALLOWANCE * 1.5 ||
		position->y + BULLET_DIMENSION.y > Background::getInstance()->getDimension().y - (BORDER_ALLOWANCE)) {
		*remove = true;
	}
}

void Bullet::update() {
	position->x += static_cast<int>(*directionX * *movementSpeed);
	position->y += static_cast<int>(*directionY * *movementSpeed);

	checkCollision();
}


void Bullet::render() {
	float angle = std::atan2(*directionY, *directionX) * (180.0f / M_PI);

	SDL_Rect dstRect = {
	position->x - Background::getInstance()->srcRect->x,
	position->y - Background::getInstance()->srcRect->y,
	BULLET_DIMENSION.x,
	BULLET_DIMENSION.y
	};

	SDL_SetRenderTarget(Game::getInstance()->getRenderer(), Background::getInstance()->background);
	SDL_RenderCopyEx(
		Game::getInstance()->getRenderer(),
		textureType->texture,
		nullptr,
		&dstRect,
		angle,
		nullptr, 
		SDL_FLIP_NONE
	);
	SDL_SetRenderTarget(Game::getInstance()->getRenderer(), nullptr);
}

std::shared_ptr<Prototype> Bullet::clone() const {
	return std::make_shared<Bullet>(*this);
}