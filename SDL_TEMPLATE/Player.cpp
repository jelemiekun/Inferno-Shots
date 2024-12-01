#include "Player.h"
#include "Command.h"

int Player::playerCounter = 0;

Player::Player(int heartCount, SDL_Point position, float movementSpeed, float speedDecay, bool inCooldown)
    : heartCount(std::make_unique<int>(heartCount)),
    position(std::make_unique<SDL_Point>(position)),
    movementSpeed(std::make_unique<float>(movementSpeed)),
    speedDecay(std::make_unique<float>(speedDecay)),
    inCooldown(std::make_unique<bool>(inCooldown)) {
    ID = std::make_unique<int>(playerCounter++);
}


void Player::update() {
    while (!commandQueue.empty()) {
        auto command = std::move(commandQueue.front());
        commandQueue.pop();
        command->execute(shared_from_this());
    }
}

void Player::render() {

}

int Player::getID() const {
    return *ID;
}

//TODO