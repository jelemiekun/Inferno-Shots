#pragma once
#include <SDL.h>
#include <memory>
#include <vector>
#include "Prototype.h"

class TextureType;

class Bullet : public Prototype {
private:
	std::shared_ptr<TextureType> textureType;
	std::unique_ptr<SDL_Point> position;
	std::unique_ptr<float> directionX;
	std::unique_ptr<float> directionY;
	std::unique_ptr<float> movementSpeed;

public:
	std::unique_ptr<bool> remove;

public:
	static constexpr SDL_Point BULLET_DIMENSION = { 30, 30 };
	static std::vector<std::unique_ptr<Bullet>> bullets;

private:
	void checkCollision();

public:
	Bullet(std::shared_ptr<TextureType> texture);
	Bullet(const Bullet& other);
	~Bullet();

	void initPos(SDL_Point initPos);
	void initDirections(float x, float y);
	void initMovementSpeed(float movementSpeed);
	void update();
	void render();

	std::shared_ptr<Prototype> clone() const override;
};