#include "Player.h"
#include "Command.h"
#include "TextureType.h"
#include "Game.h"
#include "Background.h"
#include "AppInfo.h"
#include "GameEnums.h"
#include "PlayerProfile.h"

int Player::playerCounter = 1;

// Constructor for prototype only, will not increment counter
Player::Player(int heartAmount, int sprintAmount,
    TextureType* textureType, SDL_Point position, float movementSpeed, float speedDecay)
    : ID(std::make_unique<int>(0)),
    textureType(std::make_unique<TextureType>(*textureType)),
    heartAmount(std::make_unique<int>(heartAmount)),
    maxSprintAmount(std::make_unique<int>(sprintAmount)),
    sprintAmount(std::make_unique<int>(sprintAmount)),
    position(std::make_unique<SDL_Point>(position)),
    movementSpeed(std::make_unique<float>(movementSpeed)),
    speedDecay(std::make_unique<float>(speedDecay)),
    inCooldown(std::make_unique<bool>(false)),
    isSprinting(std::make_unique<bool>(false)),
    isMoving(std::make_unique<bool>(false)),
    frameCounter(std::make_unique<int>(0)),
    directionX(std::make_unique<float>()),
    directionY(std::make_unique<float>()),
    directionFacing(Face_Direction::DOWN),
    isMovingLeft(std::make_unique<bool>(false)), 
    isMovingUpLeft(std::make_unique<bool>(false)), 
    isMovingUp(std::make_unique<bool>(false)), 
    isMovingUpRight(std::make_unique<bool>(false)), 
    isMovingRight(std::make_unique<bool>(false)), 
    isMovingDownRight(std::make_unique<bool>(false)), 
    isMovingDown(std::make_unique<bool>(false)), 
    isMovingDownLeft(std::make_unique<bool>(false)) {

    platformPosition = std::make_unique<SDL_Point>(SDL_Point{
        position.x + (Player::PLAYER_DIMENSION.x / 2) + Background::getInstance()->srcRect->x,
        position.y + (Player::PLAYER_DIMENSION.y / 2) + Background::getInstance()->srcRect->y
        });
}

Player::Player(const Player& other)
    : ID(std::make_unique<int>(playerCounter++)),
    textureType(std::make_unique<TextureType>(*other.textureType)),
    heartAmount(std::make_unique<int>(*other.heartAmount)),
    maxSprintAmount(std::make_unique<int>(*other.sprintAmount)),
    sprintAmount(std::make_unique<int>(*other.sprintAmount)),
    position(std::make_unique<SDL_Point>(*other.position)),
    movementSpeed(std::make_unique<float>(*other.movementSpeed)),
    speedDecay(std::make_unique<float>(*other.speedDecay)),
    inCooldown(std::make_unique<bool>(*other.inCooldown)),
    isSprinting(std::make_unique<bool>(false)),
    isMoving(std::make_unique<bool>(false)),
    frameCounter(std::make_unique<int>(0)),
    directionX(std::make_unique<float>()),
    directionY(std::make_unique<float>()),
    platformPosition(std::make_unique<SDL_Point>(*other.platformPosition)),
    playerProfile(std::make_unique<PlayerProfile>()),
    directionFacing(Face_Direction::DOWN),
    isMovingLeft(std::make_unique<bool>(false)),
    isMovingUpLeft(std::make_unique<bool>(false)),
    isMovingUp(std::make_unique<bool>(false)),
    isMovingUpRight(std::make_unique<bool>(false)),
    isMovingRight(std::make_unique<bool>(false)),
    isMovingDownRight(std::make_unique<bool>(false)),
    isMovingDown(std::make_unique<bool>(false)),
    isMovingDownLeft(std::make_unique<bool>(false)) {}

void Player::isCommandMove(Command* command) {
    if (dynamic_cast<MoveLeftCommand*>(command) ||
        dynamic_cast<MoveUpCommand*>(command) ||
        dynamic_cast<MoveRightCommand*>(command) ||
        dynamic_cast<MoveDownCommand*>(command)) {
        *isMoving = true;
    }
}

void Player::updateMove() {
    if (*isMovingLeft) {
        float newMovementSpeed = *movementSpeed;

        if (*isSprinting) newMovementSpeed += Player::SPEED_AMOUNT;

        if (Background::getInstance()->isRightEdge()) {
            position->x -= static_cast<int>(newMovementSpeed);

            if (position->x <= (SCREEN_WIDTH / 2)) {
                Background::getInstance()->srcRect->x -= static_cast<int>(newMovementSpeed);
            }
        } else if (Background::getInstance()->isLeftEdge()) {
            Background::getInstance()->srcRect->x = 0;
            position->x -= static_cast<int>(newMovementSpeed);

            if (position->x < BORDER_ALLOWANCE) {
                position->x = BORDER_ALLOWANCE;
            }
        } else {
            Background::getInstance()->srcRect->x -= static_cast<int>(newMovementSpeed);
        }
    }
    if (*isMovingUp) {
        float newMovementSpeed = *movementSpeed;

        if (*isSprinting) newMovementSpeed += Player::SPEED_AMOUNT;

        if (Background::getInstance()->isDownEdge()) {
            position->y -= static_cast<int>(newMovementSpeed);

            if (position->y <= (SCREEN_HEIGHT / 2)) {
                Background::getInstance()->srcRect->y -= static_cast<int>(newMovementSpeed);
            }
        } else if (Background::getInstance()->isUpEdge()) {
            Background::getInstance()->srcRect->y = 0;
            position->y -= static_cast<int>(newMovementSpeed);

            if (position->y < BORDER_ALLOWANCE) {
                position->y = BORDER_ALLOWANCE;
            }
        } else {
            Background::getInstance()->srcRect->y -= static_cast<int>(newMovementSpeed);
        }
    }
    if (*isMovingRight) {
        float newMovementSpeed = *movementSpeed;

        if (*isSprinting) newMovementSpeed += Player::SPEED_AMOUNT;

        if (Background::getInstance()->isLeftEdge()) {
            position->x += static_cast<int>(newMovementSpeed);

            if (position->x >= (SCREEN_WIDTH / 2)) {
                Background::getInstance()->srcRect->x += static_cast<int>(newMovementSpeed);
            }
        } else if (Background::getInstance()->isRightEdge()) {
            position->x += static_cast<int>(newMovementSpeed);

            if (position->x > SCREEN_WIDTH - BORDER_ALLOWANCE - Player::PLAYER_DIMENSION.x) {
                position->x = SCREEN_WIDTH - BORDER_ALLOWANCE - Player::PLAYER_DIMENSION.x;
            }
        } else {
            Background::getInstance()->srcRect->x += static_cast<int>(newMovementSpeed);
        }
    }
    if (*isMovingDown) {
        float newMovementSpeed = *movementSpeed;

        if (*isSprinting) newMovementSpeed += Player::SPEED_AMOUNT;

        if (Background::getInstance()->isUpEdge()) {
            position->y += static_cast<int>(newMovementSpeed);

            if (position->y >= (SCREEN_HEIGHT / 2)) {
                Background::getInstance()->srcRect->y += static_cast<int>(newMovementSpeed);
            }
        } else if (Background::getInstance()->isDownEdge()) {
            position->y += static_cast<int>(newMovementSpeed);

            if (position->y > SCREEN_HEIGHT - BORDER_ALLOWANCE - Player::PLAYER_DIMENSION.y) {
                position->y = SCREEN_HEIGHT - BORDER_ALLOWANCE - Player::PLAYER_DIMENSION.y;
            }
        } else {
            Background::getInstance()->srcRect->y += static_cast<int>(newMovementSpeed);
        }
    }
}

void Player::updatePlatformPosition() {
    platformPosition->x = position->x + (Player::PLAYER_DIMENSION.x / 2) + Background::getInstance()->srcRect->x;
    platformPosition->y = position->y + (Player::PLAYER_DIMENSION.y / 2) + Background::getInstance()->srcRect->y;
}

void Player::initProfile() const {
    playerProfile->init(*ID, *heartAmount, *maxSprintAmount);
}


void Player::update() {
    *isMoving = false;

    while (!commandQueue.empty()) {
        auto command = std::move(commandQueue.front());
        commandQueue.pop();
        command->execute(shared_from_this());
        
        isCommandMove(command.get());
    }

    updateMove();
    updatePlatformPosition();

    playerProfile->update(*heartAmount, *maxSprintAmount);
}

void Player::render() const {
    SDL_Rect srcRect = { 0, 0, textureType->dimension.x, textureType->dimension.y / 8 };

    switch (directionFacing) {
    case Face_Direction::LEFT:      srcRect.y = (textureType->dimension.y / 8) * 2; break;
    case Face_Direction::UP_LEFT:   srcRect.y = (textureType->dimension.y / 8) * 4; break;
    case Face_Direction::UP:        srcRect.y = (textureType->dimension.y / 8) * 0; break;
    case Face_Direction::UP_RIGHT:  srcRect.y = (textureType->dimension.y / 8) * 5; break;
    case Face_Direction::RIGHT:     srcRect.y = (textureType->dimension.y / 8) * 3; break;
    case Face_Direction::DOWN_RIGHT:srcRect.y = (textureType->dimension.y / 8) * 7; break;
    case Face_Direction::DOWN:      srcRect.y = (textureType->dimension.y / 8) * 1; break;
    case Face_Direction::DOWN_LEFT: srcRect.y = (textureType->dimension.y / 8) * 6; break;
    default: break;
    }
    SDL_Rect dstRect = { position->x, position->y, Player::PLAYER_DIMENSION.x, Player::PLAYER_DIMENSION.y };
    SDL_RenderCopy(Game::getInstance()->getRenderer(), textureType->texture, &srcRect, &dstRect);   
}

void Player::renderPlayerProfiles() const {
    playerProfile->render();
}

int Player::getID() const {
    return *ID;
}

std::shared_ptr<Prototype> Player::clone() const {
    return std::make_shared<Player>(*this);
}