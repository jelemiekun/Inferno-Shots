#include "Command.h"
#include "Player.h"

// Move Commands

void MoveLeftComand::execute(std::shared_ptr<Player> player) {
    player->position->x -= static_cast<int>(*player->movementSpeed);
}

void MoveUpLeftComand::execute(std::shared_ptr<Player> player) {
    player->position->x -= static_cast<int>(*player->movementSpeed);
    player->position->y -= static_cast<int>(*player->movementSpeed);
}

void MoveUpComand::execute(std::shared_ptr<Player> player) {
    player->position->y -= static_cast<int>(*player->movementSpeed);
}

void MoveUpRightComand::execute(std::shared_ptr<Player> player) {
    player->position->x += static_cast<int>(*player->movementSpeed);
    player->position->y -= static_cast<int>(*player->movementSpeed);
}

void MoveRightComand::execute(std::shared_ptr<Player> player) {
    player->position->x += static_cast<int>(*player->movementSpeed);
}

void MoveDownRightComand::execute(std::shared_ptr<Player> player) {
    player->position->x += static_cast<int>(*player->movementSpeed);
    player->position->y += static_cast<int>(*player->movementSpeed);
}

void MoveDownComand::execute(std::shared_ptr<Player> player) {
    player->position->y += static_cast<int>(*player->movementSpeed);
}

void MoveDownLeftComand::execute(std::shared_ptr<Player> player) {
    player->position->x -= static_cast<int>(*player->movementSpeed);
    player->position->y += static_cast<int>(*player->movementSpeed);
}

// Face Direction Commands

void FaceLeftComand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::LEFT;
}

void FaceUpLeftComand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::UP_LEFT;
}

void FaceUpComand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::UP;
}

void FaceUpRightComand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::UP_RIGHT;
}

void FaceRightComand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::RIGHT;
}

void FaceDownRightComand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::DOWN_RIGHT;
}

void FaceDownComand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::DOWN;
}

void FaceDownLeftComand::execute(std::shared_ptr<Player> player) {
    player->directionFacing = Face_Direction::DOWN_LEFT;
}

// Sprint

void SprintCommand::execute(std::shared_ptr<Player> player) {
    *player->movementSpeed += 10;
}

// Fire

void FireCommans::execute(std::shared_ptr<Player> player) {
    // Empty implementation
}
