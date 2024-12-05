#include "Command.h"
#include "Player.h"
#include "TextureType.h"
#include "Background.h"
#include "AppInfo.h"
#include "GameEnums.h"
#include "Bullet.h"
#include "PrototypeRegistry.h"

// Move Commands

void MoveLeftCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingLeft = true;
}


void MoveUpCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingUp = true;
}


void MoveRightCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingRight = true;
}


void MoveDownCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingDown = true;
}


// KeyUp Move Commands

void KeyUpMoveLeftCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingLeft = false;
}


void KeyUpMoveUpCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingUp = false;
}


void KeyUpMoveRightCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingRight = false;
}


void KeyUpMoveDownCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingDown = false;
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
    std::shared_ptr<Bullet> sharedBullet = std::dynamic_pointer_cast<Bullet>(
        PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::BULLET)
    );

    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(*sharedBullet);

    SDL_Point fixedPos = {
        player->position->x + (Player::PLAYER_DIMENSION.x / 2) + Background::getInstance()->srcRect->x,
        player->position->y + (Player::PLAYER_DIMENSION.y / 2) + Background::getInstance()->srcRect->y
    };

    bullet->initPos(fixedPos);
    bullet->initDirections( *player->directionX, *player->directionY);
    bullet->initMovementSpeed(Player::BULLET_SPEED_SCALAR);

    static std::shared_ptr<TextureType> bulletTexture = std::make_shared<TextureType>(Prototype_Type::BULLET);
    bullet->initTexture(bulletTexture);

    Bullet::bullets.push_back(std::move(bullet));
}