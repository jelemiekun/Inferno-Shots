#pragma once
#include <SDL.h>
#include <queue>
#include <memory>

using Vector = SDL_Point;

class Command;

enum class Face_Direction {
	LEFT,
	UP_LEFT,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT
};

class Player : public std::enable_shared_from_this<Player> {
private:
	static int playerCounter;

private:
	std::unique_ptr<int> ID;
	std::unique_ptr<int> heartCount;
	std::unique_ptr<SDL_Point> position;
	std::unique_ptr<float> movementSpeed;
	std::unique_ptr<float> speedDecay;
	std::unique_ptr<bool> inCooldown;
	Face_Direction directionFacing;

public:
	std::queue<std::shared_ptr<Command>> commandQueue;

public:
	Player(int heartCount, SDL_Point position, float movementSpeed, float speedDecay, bool inCooldown);
	~Player() = default;

	void input(SDL_Event& gEvent);
	void update();
	void render();

	int getID() const;
};

