#include "Player.h"
#include "Command.h"
#include "TextureType.h"
#include "Game.h"

int Player::playerCounter = 1;

// Constructor for prototype only, will not increment counter
Player::Player(int heartCount, TextureType* textureType, SDL_Point position, float movementSpeed, float speedDecay)
    : ID(std::make_unique<int>(0)),
    textureType(std::make_unique<TextureType>(*textureType)),
    heartCount(std::make_unique<int>(heartCount)),
    position(std::make_unique<SDL_Point>(position)),
    movementSpeed(std::make_unique<float>(movementSpeed)),
    speedDecay(std::make_unique<float>(speedDecay)),
    inCooldown(std::make_unique<bool>(false)),
    directionFacing(Face_Direction::DOWN) {
}

Player::Player(const Player& other)
    : ID(std::make_unique<int>(playerCounter++)),
    textureType(std::make_unique<TextureType>(*other.textureType)),
    heartCount(std::make_unique<int>(*other.heartCount)),
    position(std::make_unique<SDL_Point>(*other.position)),
    movementSpeed(std::make_unique<float>(*other.movementSpeed)),
    speedDecay(std::make_unique<float>(*other.speedDecay)),
    inCooldown(std::make_unique<bool>(*other.inCooldown)),
    directionFacing(Face_Direction::DOWN) {
}



void Player::update() {
    while (!commandQueue.empty()) {
        auto command = std::move(commandQueue.front());
        commandQueue.pop();
        command->execute(shared_from_this());
    }
}

void Player::render() {
    SDL_Rect srcRect = { 0, 0, textureType->dimension.x / 4, textureType->dimension.y / 8 };
    SDL_Rect dstRect = { position->x, position->y, ENTITY_DIMENSION.x, ENTITY_DIMENSION.y };
    SDL_RenderCopy(Game::getInstance()->getRenderer(), textureType->texture, &srcRect, &dstRect);
}

int Player::getID() const {
    return *ID;
}

std::shared_ptr<Prototype> Player::clone() const {
    return std::make_shared<Player>(*this);
}