#pragma once
#include <SDL.h>
#include <queue>
#include <memory>
#include "GameEnums.h"
#include "Prototype.h"

using Vector = SDL_Point;

class Command;
class TextureType;

class Player : 
	public Prototype, public std::enable_shared_from_this<Player> {
private:
	static int playerCounter;

public:
	std::unique_ptr<int> ID;
	std::unique_ptr<TextureType> textureType;
	std::unique_ptr<int> heartCount;
	std::unique_ptr<SDL_Point> position;
	std::unique_ptr<float> movementSpeed;
	std::unique_ptr<float> speedDecay;
	std::unique_ptr<bool> inCooldown;
	Face_Direction directionFacing;

public:
	std::queue<std::shared_ptr<Command>> commandQueue;

public:
	Player(int heartCount, TextureType* textureType, SDL_Point position, float movementSpeed, float speedDecay);
	Player(const Player& other);
	~Player() = default;

	void update();
	void render();

	int getID() const;

	std::shared_ptr<Prototype> clone() const override;
};

