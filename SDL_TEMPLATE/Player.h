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
class Enemy;
class Bullet;

class Player : 
	public Prototype, public std::enable_shared_from_this<Player> {
private:
	constexpr static int HEALTH_ADDER_COOLDOWN = 700;
	constexpr static int HEALTH_ADDER = 1;
public:
	constexpr static Dimension PLAYER_DIMENSION = { 45, 45 };
	constexpr static int SPEED_AMOUNT = 3;
	constexpr static int BULLET_SPEED_SCALAR = 10;

public:
	static int playerCounter;
	static std::string staticStringPlayerName;

public:
	std::unique_ptr<int> ID;
	std::unique_ptr<TextureType> textureType;
	std::unique_ptr<int> maxHeartAmount;
	std::unique_ptr<int> heartAmount;
	std::unique_ptr<int> maxSprintAmount;
	std::unique_ptr<int> sprintAmount;
	std::unique_ptr<SDL_Point> position;
	std::unique_ptr<float> movementSpeed;
	std::unique_ptr<float> speedDecay;
	std::unique_ptr<bool> inCooldown;
	std::unique_ptr<bool> isSprinting;
	std::unique_ptr<bool> isMoving;
	std::unique_ptr<bool> isFiring;
	std::unique_ptr<Uint32> firingCooldown;
	std::unique_ptr<int> score;
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
	std::unique_ptr<SDL_Rect> dstRectMonitor;
	
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
	void setDeadColor();
	void firing();
	void takeDamage(int damage);
	void addScore(int score);
	std::unique_ptr<Bullet> getBulletPrototype();
	bool canFire() const;
	SDL_Point getBulletPosition() const;
	SDL_Rect getEnemyRect(Enemy& enemy);
	SDL_Rect getPlayerRectPlatform();
	SDL_Rect getDstRectTextPlayerName();
	SDL_Rect getSrcRectDirectionFacing();
	void heal();

	void checkSprint();
	void checkFiring();
	void updateCommandQueue();
	void updateMove();
	void updatePlatformPosition();
	void updateMonitorPosition();
	void checkCollisionWithEnemies();
	bool canHeal() const;
	void checkHealth();
	void updateTextPlayerPosition();


public:
	std::queue<std::shared_ptr<Command>> commandQueue;

public:
	Player(int heartCount, int sprintAmount, TextureType* textureType, SDL_Point position, float movementSpeed, float speedDecay);
	Player(const Player& other);
	~Player() = default;

	void initProfile();
	void updateProfileName();
	void update();
	void render();
	void renderPlayerProfiles() const;

	int getID() const;
	std::shared_ptr<Prototype> clone() const override;
};

