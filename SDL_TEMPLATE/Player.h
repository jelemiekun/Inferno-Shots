#pragma once
#include <SDL.h>
#include <queue>
#include <memory>
#include "GameEnums.h"
#include "Prototype.h"

using Vector = SDL_Point;

class Command;
class TextureType;
class PlayerProfile;
class Text;

class Player : 
	public Prototype, public std::enable_shared_from_this<Player> {
private:
	static int playerCounter;
	constexpr static int UNIQUE_FRAME_COUNT = 4;
	constexpr static int FRAME_DURATION = 50;
public:
	constexpr static Dimension PLAYER_DIMENSION = { 45, 45 };
	constexpr static int SPEED_AMOUNT = 3;
	constexpr static int BULLET_SPEED_SCALAR = 10;

public:
	std::unique_ptr<int> ID;
	std::unique_ptr<TextureType> textureType;
	std::unique_ptr<int> heartAmount;
	std::unique_ptr<int> maxSprintAmount;
	std::unique_ptr<int> sprintAmount;
	std::unique_ptr<SDL_Point> position;
	std::unique_ptr<float> movementSpeed;
	std::unique_ptr<float> speedDecay;
	std::unique_ptr<bool> inCooldown;
	std::unique_ptr<bool> isSprinting;
	std::unique_ptr<bool> isMoving;
	std::unique_ptr<int> frameCounter;
	std::unique_ptr<float> directionX;
	std::unique_ptr<float> directionY;
	std::unique_ptr<SDL_Point> platformPosition;
	std::unique_ptr<PlayerProfile> playerProfile;
	std::unique_ptr<bool> alive;
	Face_Direction directionFacing;
	std::unique_ptr<SDL_Texture*> deadColorTexture;
	std::unique_ptr<Text> textPlayerName;
	std::unique_ptr<Text> textPlayerPosition;
	std::unique_ptr<std::string> stringPlayerName;
	std::unique_ptr<SDL_Rect> dstRectPlatform;
	
	std::unique_ptr<bool> isMovingLeft;
	std::unique_ptr<bool> isMovingUpLeft;
	std::unique_ptr<bool> isMovingUp;
	std::unique_ptr<bool> isMovingUpRight;
	std::unique_ptr<bool> isMovingRight;
	std::unique_ptr<bool> isMovingDownRight;
	std::unique_ptr<bool> isMovingDown;
	std::unique_ptr<bool> isMovingDownLeft;

private:
	void isCommandMove(Command* command);
	void updateMove();
	void updatePlatformPosition();
	void checkHealth();
	void setDeadColor();
	SDL_Rect getDstRectTextPlayerName();
	SDL_Rect getSrcRectDirectionFacing();

public:
	std::queue<std::shared_ptr<Command>> commandQueue;

public:
	Player(int heartCount, int sprintAmount, TextureType* textureType, SDL_Point position, float movementSpeed, float speedDecay);
	Player(const Player& other);
	~Player() = default;

	void initProfile();
	void update();
	void render();
	void renderPlayerProfiles() const;

	int getID() const;
	std::shared_ptr<Prototype> clone() const override;
};

