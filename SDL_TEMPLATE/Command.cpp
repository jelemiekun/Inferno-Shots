#include "Command.h"
#include "Player.h"

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
    *player->isFiring = true;
}

void UnfireCommand::execute(std::shared_ptr<Player> player) {
    *player->isFiring = false;
}