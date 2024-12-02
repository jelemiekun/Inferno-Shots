#include "Player.h"
#include "Command.h"

int Player::playerCounter = 0;

Player::Player(int heartCount, SDL_Point position, float movementSpeed, float speedDecay)
    : ID(std::make_unique<int>(playerCounter++)),
    heartCount(std::make_unique<int>(heartCount)),
    position(std::make_unique<SDL_Point>(position)),
    movementSpeed(std::make_unique<float>(movementSpeed)),
    speedDecay(std::make_unique<float>(speedDecay)),
    inCooldown(std::make_unique<bool>(false)) {}


Player::Player(const Player& other)
    : heartCount(std::make_unique<int>(*other.heartCount)),
    position(std::make_unique<SDL_Point>(*other.position)),
    movementSpeed(std::make_unique<float>(*other.movementSpeed)),
    speedDecay(std::make_unique<float>(*other.speedDecay)),
    inCooldown(std::make_unique<bool>(*other.inCooldown)),
    directionFacing(other.directionFacing) {
    ID = std::make_unique<int>(playerCounter++);
    directionFacing = Face_Direction::DOWN;
}



void Player::update() {
    while (!commandQueue.empty()) {
        auto command = std::move(commandQueue.front());
        commandQueue.pop();
        command->execute(shared_from_this());
    }
}

void Player::render() {
    // TODO
}

int Player::getID() const {
    return *ID;
}

std::shared_ptr<Prototype> Player::clone() const {
    return std::make_shared<Player>(*this);
}