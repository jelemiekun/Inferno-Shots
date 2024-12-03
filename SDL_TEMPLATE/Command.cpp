#include "Command.h"
#include "Player.h"
#include "TextureType.h"
#include "Background.h"
#include "AppInfo.h"
#include "GameEnums.h"
#include "Bullet.h"
#include "PrototypeRegistry.h"

// Move Commands

constexpr static int BORDER_ALLOWANCE = 12;

void MoveLeftCommand::execute(std::shared_ptr<Player> player) {
    int movementSpeed = *player->movementSpeed;

    if (*player->isSprinting) movementSpeed += Player::SPEED_AMOUNT;

    if (Background::getInstance()->isRightEdge()) {
        player->position->x -= static_cast<int>(movementSpeed);

        if (player->position->x <= (SCREEN_WIDTH / 2)) {
            Background::getInstance()->srcRect->x -= static_cast<int>(movementSpeed);
        }
    } else if (Background::getInstance()->isLeftEdge()) {
        Background::getInstance()->srcRect->x = 0;
        player->position->x -= static_cast<int>(movementSpeed);

        if (player->position->x < BORDER_ALLOWANCE) {
            player->position->x = BORDER_ALLOWANCE;
        }
    } else {
        Background::getInstance()->srcRect->x -= static_cast<int>(movementSpeed);
    }
}

void MoveUpLeftCommand::execute(std::shared_ptr<Player> player) {
    MoveUpCommand moveUp;
    MoveLeftCommand moveLeft;

    moveUp.execute(player);
    moveLeft.execute(player);
}

void MoveUpCommand::execute(std::shared_ptr<Player> player) {
    int movementSpeed = *player->movementSpeed;

    if (*player->isSprinting) movementSpeed += Player::SPEED_AMOUNT;

    if (Background::getInstance()->isDownEdge()) {
        player->position->y -= static_cast<int>(movementSpeed);

        if (player->position->y <= (SCREEN_HEIGHT / 2)) {
            Background::getInstance()->srcRect->y -= static_cast<int>(movementSpeed);
        }
    } else if (Background::getInstance()->isUpEdge()) {
        Background::getInstance()->srcRect->y = 0;
        player->position->y -= static_cast<int>(movementSpeed);

        if (player->position->y < BORDER_ALLOWANCE) {
            player->position->y = BORDER_ALLOWANCE;
        }
    } else {
        Background::getInstance()->srcRect->y -= static_cast<int>(movementSpeed);
    }
}

void MoveUpRightCommand::execute(std::shared_ptr<Player> player) {
    MoveUpCommand moveUp;
    MoveRightCommand moveRight;

    moveUp.execute(player);
    moveRight.execute(player);
}

void MoveRightCommand::execute(std::shared_ptr<Player> player) {
    int movementSpeed = *player->movementSpeed;

    if (*player->isSprinting) movementSpeed += Player::SPEED_AMOUNT;

    if (Background::getInstance()->isLeftEdge()) {
        player->position->x += static_cast<int>(movementSpeed);

        if (player->position->x >= (SCREEN_WIDTH / 2)) {
            Background::getInstance()->srcRect->x += static_cast<int>(movementSpeed);
        }
    } else if (Background::getInstance()->isRightEdge()) {
        player->position->x += static_cast<int>(movementSpeed);

        if (player->position->x > SCREEN_WIDTH - BORDER_ALLOWANCE - ENTITY_DIMENSION.x) {
            player->position->x = SCREEN_WIDTH - BORDER_ALLOWANCE - ENTITY_DIMENSION.x;
        }
    } else {
        Background::getInstance()->srcRect->x += static_cast<int>(movementSpeed);
    }
}

void MoveDownRightCommand::execute(std::shared_ptr<Player> player) {
    MoveDownCommand moveDown;
    MoveRightCommand moveRight;

    moveDown.execute(player);
    moveRight.execute(player);
}

void MoveDownCommand::execute(std::shared_ptr<Player> player) {
    int movementSpeed = *player->movementSpeed;

    if (*player->isSprinting) movementSpeed += Player::SPEED_AMOUNT;

    if (Background::getInstance()->isUpEdge()) {
        player->position->y += static_cast<int>(movementSpeed);

        if (player->position->y >= (SCREEN_HEIGHT / 2)) {
            Background::getInstance()->srcRect->y += static_cast<int>(movementSpeed);
        }
    } else if (Background::getInstance()->isDownEdge()) {
        player->position->y += static_cast<int>(movementSpeed);

        if (player->position->y > SCREEN_HEIGHT - BORDER_ALLOWANCE - ENTITY_DIMENSION.y) {
            player->position->y = SCREEN_HEIGHT - BORDER_ALLOWANCE - ENTITY_DIMENSION.y;
        }
    } else {
        Background::getInstance()->srcRect->y += static_cast<int>(movementSpeed);
    }
}

void MoveDownLeftCommand::execute(std::shared_ptr<Player> player) {
    MoveDownCommand moveDown;
    MoveLeftCommand moveLeft;

    moveDown.execute(player);
    moveLeft.execute(player);
}

// Face Direction Commands

void FaceLeftCommand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::LEFT;
}

void FaceUpLeftCommand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::UP_LEFT;
}

void FaceUpCommand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::UP;
}

void FaceUpRightCommand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::UP_RIGHT;
}

void FaceRightCommand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::RIGHT;
}

void FaceDownRightCommand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::DOWN_RIGHT;
}

void FaceDownCommand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::DOWN;
}

void FaceDownLeftCommand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::DOWN_LEFT;
}

// Sprint

void SprintCommand::execute(std::shared_ptr<Player> player) {
    *player->isSprinting = true;
}

void RemoveSprintCommand::execute(std::shared_ptr<Player> player) {
    *player->isSprinting = false;
}

// Fire

void FireCommand::execute(std::shared_ptr<Player> player) {
    std::cout << "FIRING!" << '\n';

    // Clone a player
    std::shared_ptr<Bullet> sharedBullet = std::dynamic_pointer_cast<Bullet>(
        PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::BULLET)
    );

    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(*sharedBullet);

    bullet->initPos(*player->position.get());
    bullet->initDirections( *player->directionX, *player->directionY);
    bullet->initMovementSpeed(Player::BULLET_SPEED_SCALAR);

    Bullet::bullets.push_back(std::move(bullet));
}