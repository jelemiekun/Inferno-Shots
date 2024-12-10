#pragma once
#include "Enemy.h"
#include "GameEnums.h"
#include <memory>
#include <SDL.h>

class Player;
class TextureType;

class EnemyType : public Enemy, public std::enable_shared_from_this<EnemyType> {
public:
	std::unique_ptr<Prototype_Type> enemyType;
	std::shared_ptr<TextureType> textureType;
	std::unique_ptr<SDL_Point> dimension;
	std::unique_ptr<int> healthCount;
	std::unique_ptr<int> damage;
	std::unique_ptr<int> score;
	std::unique_ptr<SDL_Point> position;
	std::unique_ptr<float> movementSpeed;
	std::unique_ptr<float> directionX;
	std::unique_ptr<float> directionY;
	std::unique_ptr<bool> dead;
	std::unique_ptr<bool> inflicted;
	std::unique_ptr<int> minimapSize;

private:
	std::shared_ptr<Player> getNearestPlayer();
	void calculateNormalizedLength(std::shared_ptr<Player> nearestPlayer);
	void move();

public:
	EnemyType(Prototype_Type enemyType, std::shared_ptr<TextureType> type, SDL_Point dimension, int healthCount, float speed, int damage, int score, int minimampSize);
	EnemyType(const EnemyType& other);

	void initPos() override;
	int getEnemyScore() override;
	void undoMove() override;
	void checkCollision() override;
	void update() override;
	void render() const override;
	std::shared_ptr<Prototype> clone() const override;
	const bool& isDead() const override;
	void setDead() override;
	void decreaseHealth() override;
	const SDL_Point& getPosition() const override;
	const SDL_Point& getDimension() const override;
	Prototype_Type getType() const override;
	int getMinimapPixelSize() override;
	const int getDamage() const override;
};

