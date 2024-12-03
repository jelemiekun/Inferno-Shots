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

void MoveUpLeftCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingLeft = true;
    *player->isMovingUp = true;
}

void MoveUpCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingUp = true;
}

void MoveUpRightCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingUp = true;
    *player->isMovingRight = true;
}

void MoveRightCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingRight = true;
}

void MoveDownRightCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingDown = true;
    *player->isMovingRight = true;
}

void MoveDownCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingDown = true;
}

void MoveDownLeftCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingDown = true;
    *player->isMovingLeft = true;
}

// KeyUp Move Commands

void KeyUpMoveLeftCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingLeft = false;
}

void KeyUpMoveUpLeftCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingUp = false;
    *player->isMovingLeft = false;
}

void KeyUpMoveUpCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingUp = false;
}

void KeyUpMoveUpRightCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingUp = false;
    *player->isMovingRight = false;
}

void KeyUpMoveRightCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingRight = false;
}

void KeyUpMoveDownRightCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingDown = false;
    *player->isMovingRight = false;
}

void KeyUpMoveDownCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingDown = false;
}

void KeyUpMoveDownLeftCommand::execute(std::shared_ptr<Player> player) {
    *player->isMovingDown = false;
    *player->isMovingLeft = false;
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
    std::cout << *player->isSprinting << '\n';
}

// Fire

void FireCommand::execute(std::shared_ptr<Player> player) {
    std::shared_ptr<Bullet> sharedBullet = std::dynamic_pointer_cast<Bullet>(
        PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::BULLET)
    );

    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(*sharedBullet);

    SDL_Point fixedPos = { 
        player->position->x + (ENTITY_DIMENSION.x / 2), 
        player->position->y + (ENTITY_DIMENSION.y / 2) 
    };

    bullet->initPos(fixedPos);
    bullet->initDirections( *player->directionX, *player->directionY);
    bullet->initMovementSpeed(Player::BULLET_SPEED_SCALAR);

    static std::shared_ptr<TextureType> bulletTexture = std::make_shared<TextureType>(Prototype_Type::BULLET);
    bullet->initTexture(bulletTexture);

    Bullet::bullets.push_back(std::move(bullet));
}