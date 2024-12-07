#pragma once
#include <SDL.h>
#include <memory>
#include <vector>
#include "Prototype.h"

class TextureType;
class Player;

class Bullet : public Prototype {
public:
	std::shared_ptr<TextureType> textureType;
	std::unique_ptr<SDL_Point> position;
private:
	std::unique_ptr<float> directionX;
	std::unique_ptr<float> directionY;
	std::unique_ptr<float> movementSpeed;
	std::shared_ptr<Player> player;

public:
	std::unique_ptr<bool> remove;

public:
	static constexpr SDL_Point BULLET_DIMENSION = { 10, 10 };
	static std::vector<std::unique_ptr<Bullet>> bullets;

private:
	void checkCollision();

public:
	Bullet();
	Bullet(const Bullet& other);
	~Bullet();

	void initPlayer(std::shared_ptr<Player> player);
	void initPos(SDL_Point initPos);
	void initDirections(float x, float y);
	void initMovementSpeed(float movementSpeed);
	void initTexture(std::shared_ptr<TextureType> textureType);
	void update();
	void render();

	std::shared_ptr<Prototype> clone() const override;
};