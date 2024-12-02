#include "Command.h"
#include "Player.h"
#include "TextureType.h"
#include "Background.h"
#include "AppInfo.h"
#include "GameEnums.h"

// Move Commands

constexpr static int BORDER_ALLOWANCE = 12;

void MoveLeftCommand::execute(std::shared_ptr<Player> player) {
    if (Background::getInstance()->isRightEdge()) {
        player->position->x -= static_cast<int>(*player->movementSpeed);

        if (player->position->x <= (SCREEN_WIDTH / 2)) {
            Background::getInstance()->srcRect->x -= static_cast<int>(*player->movementSpeed);
        }
    } else if (Background::getInstance()->isLeftEdge()) {
        Background::getInstance()->srcRect->x = 0;
        player->position->x -= static_cast<int>(*player->movementSpeed);

        if (player->position->x < BORDER_ALLOWANCE) {
            player->position->x = BORDER_ALLOWANCE;
        }
    } else {
        Background::getInstance()->srcRect->x -= static_cast<int>(*player->movementSpeed);
    }
}

void MoveUpLeftCommand::execute(std::shared_ptr<Player> player) {
    MoveUpCommand moveUp;
    MoveLeftCommand moveLeft;

    moveUp.execute(player);
    moveLeft.execute(player);
}

void MoveUpCommand::execute(std::shared_ptr<Player> player) {
    if (Background::getInstance()->isDownEdge()) {
        player->position->y -= static_cast<int>(*player->movementSpeed);

        if (player->position->y <= (SCREEN_HEIGHT / 2)) {
            Background::getInstance()->srcRect->y -= static_cast<int>(*player->movementSpeed);
        }
    } else if (Background::getInstance()->isUpEdge()) {
        Background::getInstance()->srcRect->y = 0;
        player->position->y -= static_cast<int>(*player->movementSpeed);

        if (player->position->y < BORDER_ALLOWANCE) {
            player->position->y = BORDER_ALLOWANCE;
        }
    } else {
        Background::getInstance()->srcRect->y -= static_cast<int>(*player->movementSpeed);
    }
}

void MoveUpRightCommand::execute(std::shared_ptr<Player> player) {
    MoveUpCommand moveUp;
    MoveRightCommand moveRight;

    moveUp.execute(player);
    moveRight.execute(player);
}

void MoveRightCommand::execute(std::shared_ptr<Player> player) {
    if (Background::getInstance()->isLeftEdge()) {
        player->position->x += static_cast<int>(*player->movementSpeed);

        if (player->position->x >= (SCREEN_WIDTH / 2)) {
            Background::getInstance()->srcRect->x += static_cast<int>(*player->movementSpeed);
        }
    } else if (Background::getInstance()->isRightEdge()) {
        player->position->x += static_cast<int>(*player->movementSpeed);

        if (player->position->x > SCREEN_WIDTH - BORDER_ALLOWANCE - ENTITY_DIMENSION.x) {
            player->position->x = SCREEN_WIDTH - BORDER_ALLOWANCE - ENTITY_DIMENSION.x;
        }
    } else {
        Background::getInstance()->srcRect->x += static_cast<int>(*player->movementSpeed);
    }
}

void MoveDownRightCommand::execute(std::shared_ptr<Player> player) {
    MoveDownCommand moveDown;
    MoveRightCommand moveRight;

    moveDown.execute(player);
    moveRight.execute(player);
}

void MoveDownCommand::execute(std::shared_ptr<Player> player) {
    if (Background::getInstance()->isUpEdge()) {
        player->position->y += static_cast<int>(*player->movementSpeed);

        if (player->position->y >= (SCREEN_HEIGHT / 2)) {
            Background::getInstance()->srcRect->y += static_cast<int>(*player->movementSpeed);
        }
    } else if (Background::getInstance()->isDownEdge()) {
        player->position->y += static_cast<int>(*player->movementSpeed);

        if (player->position->y > SCREEN_HEIGHT - BORDER_ALLOWANCE - ENTITY_DIMENSION.y) {
            player->position->y = SCREEN_HEIGHT - BORDER_ALLOWANCE - ENTITY_DIMENSION.y;
        }
    } else {
        Background::getInstance()->srcRect->y += static_cast<int>(*player->movementSpeed);
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
    *player->movementSpeed += 10;
}

// Fire

void FireCommand::execute(std::shared_ptr<Player> player) {
    // Empty implementation
}
