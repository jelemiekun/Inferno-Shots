#pragma once
#include "Enemy.h"
#include <memory>
#include <SDL.h>

class Player;
class TextureType;

class NormalEnemy : public Enemy, public std::enable_shared_from_this<NormalEnemy> {
public:
	constexpr static SDL_Point NORMAL_ENEMY_DIMENSION = { 30, 30 };
	std::shared_ptr<TextureType> textureType;
	std::unique_ptr<SDL_Point> position;
	std::unique_ptr<float> movementSpeed;
	std::unique_ptr<float> directionX;
	std::unique_ptr<float> directionY;
	std::unique_ptr<bool> dead;

private:
	std::shared_ptr<Player> getNearestPlayer();
	void calculateNormalizedLength(std::shared_ptr<Player> nearestPlayer);
	
	void move();

public:
	NormalEnemy(std::shared_ptr<TextureType> type);
	NormalEnemy(const NormalEnemy& other);

	void initPos() override;
	void undoMove() override;
	void checkCollision() override;
	void update() override;
	void render() const override;
	std::shared_ptr<Prototype> clone() const override;
	const bool& isDead() const override;
};

