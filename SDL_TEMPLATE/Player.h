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
	constexpr static int UNIQUE_FRAME_COUNT = 4;
	constexpr static int FRAME_DURATION = 50;

public:
	constexpr static int SPEED_AMOUNT = 7;
	constexpr static int BULLET_SPEED_SCALAR = 10;

public:
	std::unique_ptr<int> ID;
	std::unique_ptr<TextureType> textureType;
	std::unique_ptr<int> heartCount;
	std::unique_ptr<SDL_Point> position;
	std::unique_ptr<float> movementSpeed;
	std::unique_ptr<float> speedDecay;
	std::unique_ptr<bool> inCooldown;
	std::unique_ptr<bool> isSprinting;
	std::unique_ptr<bool> isMoving;
	std::unique_ptr<int> frameCounter;
	std::unique_ptr<float> directionX;
	std::unique_ptr<float> directionY;
	Face_Direction directionFacing;

private:
	void isCommandMove(Command* command);

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

