#include "Player.h"
#include "Command.h"
#include "TextureType.h"
#include "Game.h"
#include "Background.h"
#include "AppInfo.h"
#include "GameEnums.h"
#include "PlayerProfile.h"
#include "Text.h"
#include <string>

int Player::playerCounter = 1;

// Constructor for prototype only, will not increment counter
Player::Player(int heartAmount, int maxSprintAmount,
    TextureType* textureType, SDL_Point position, float movementSpeed, float speedDecay)
    : ID(std::make_unique<int>(0)),
    textureType(std::make_unique<TextureType>(*textureType)),
    heartAmount(std::make_unique<int>(heartAmount)),
    maxSprintAmount(std::make_unique<int>(maxSprintAmount)),
    sprintAmount(std::make_unique<int>(maxSprintAmount)),
    position(std::make_unique<SDL_Point>(position)),
    movementSpeed(std::make_unique<float>(movementSpeed)),
    speedDecay(std::make_unique<float>(speedDecay)){

    platformPosition = std::make_unique<SDL_Point>(SDL_Point{
        position.x + (Player::PLAYER_DIMENSION.x / 2) + Background::getInstance()->srcRect->x,
        position.y + (Player::PLAYER_DIMENSION.y / 2) + Background::getInstance()->srcRect->y
        });
}

Player::Player(const Player& other)
    : ID(std::make_unique<int>(playerCounter++)),
    textureType(std::make_unique<TextureType>(*other.textureType)),
    heartAmount(std::make_unique<int>(*other.heartAmount)),
    maxSprintAmount(std::make_unique<int>(*other.maxSprintAmount)),
    sprintAmount(std::make_unique<int>(*other.sprintAmount)),
    position(std::make_unique<SDL_Point>(*other.position)),
    movementSpeed(std::make_unique<float>(*other.movementSpeed)),
    speedDecay(std::make_unique<float>(*other.speedDecay)),
    inCooldown(std::make_unique<bool>(false)),
    isSprinting(std::make_unique<bool>(false)),
    isMoving(std::make_unique<bool>(false)),
    frameCounter(std::make_unique<int>(0)),
    directionX(std::make_unique<float>()),
    directionY(std::make_unique<float>()),
    platformPosition(std::make_unique<SDL_Point>(*other.platformPosition)),
    playerProfile(std::make_unique<PlayerProfile>()),
    alive(std::make_unique<bool>(true)),
    directionFacing(Face_Direction::DOWN),
    deadColorTexture(std::make_unique<SDL_Texture*>()),
    textPlayerName(std::make_unique<Text>()),
    textPlayerPosition(std::make_unique<Text>()),
    stringPlayerName(std::make_unique<std::string>("Player")), //TODO
    dstRectPlatform(std::make_unique<SDL_Rect>()),
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
    float newMovementSpeed = *movementSpeed;
    if (*isSprinting) {
        if (*sprintAmount < 0) {
            *sprintAmount = 0;
        } else {
            newMovementSpeed += Player::SPEED_AMOUNT;
            *sprintAmount -= 6;
        }
    }

    if (*isMovingLeft) {
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

void Player::checkHealth() {
    if (*heartAmount < 1) {
        *alive = false;
    }
}

void Player::setDeadColor() {
    SDL_Renderer* renderer = Game::getInstance()->getRenderer();

    if (deadColorTexture) SDL_DestroyTexture(*deadColorTexture);

    int textureWidth, textureHeight;
    SDL_QueryTexture(textureType->texture, nullptr, nullptr, &textureWidth, &textureHeight);

    SDL_Texture* tempTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);
    if (!tempTexture) {
        std::cerr << "Failed to create temp texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_SetRenderTarget(renderer, tempTexture);
    SDL_RenderCopy(renderer, textureType->texture, nullptr, nullptr);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, textureWidth, textureHeight, 32, SDL_PIXELFORMAT_RGBA8888);
    SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_RGBA8888, surface->pixels, surface->pitch);

    deadColorTexture = std::make_unique<SDL_Texture*>(SDL_CreateTextureFromSurface(renderer, surface));
    SDL_SetTextureColorMod(*deadColorTexture, 98, 98, 98);

    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_DestroyTexture(tempTexture);
}

SDL_Rect Player::getDstRectTextPlayerName() {
    SDL_Rect dstRect = { 0, 15, 110, 35 }; // 105
    dstRect.x = 105 * *ID + ((dstRect.w + 35) * (*ID - 1));

    return dstRect;
}

SDL_Rect Player::getSrcRectDirectionFacing() {
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
    return srcRect;
}

void Player::initProfile() {
    playerProfile->init(*ID, *heartAmount, *maxSprintAmount);

    textPlayerName->setFont(Font::MOTION_CONTROL_BOLD);
    textPlayerName->setText("Player 1");
    textPlayerName->setDstRect(getDstRectTextPlayerName());
    textPlayerName->setColor({ 255, 255, 255, 255 });
    textPlayerName->loadText();

    textPlayerPosition->setFont(Font::MOTION_CONTROL_BOLD);
    textPlayerPosition->setDstRect({ 1080, 160, 85, 30 });
    textPlayerPosition->setColor({ 255, 255, 255, 255 });
}

void Player::update() {
    if (*alive) {
        checkHealth();

        if (!(*alive)) setDeadColor();

        *isMoving = false;

        while (!commandQueue.empty()) {
            auto command = std::move(commandQueue.front());
            commandQueue.pop();
            command->execute(shared_from_this());

            isCommandMove(command.get());
        }

        updateMove();
        updatePlatformPosition();


        if (*sprintAmount < *maxSprintAmount) {
            *sprintAmount += 3;

            if (*sprintAmount > *maxSprintAmount)
                *sprintAmount = *maxSprintAmount;
        }



        textPlayerPosition->setText(
            " x:" + std::to_string(platformPosition->x - 34) + 
            "  y:" + std::to_string(platformPosition->y - 34) + " "
        );
        textPlayerPosition->loadText();
    }

    *dstRectPlatform = {position->x, position->y, Player::PLAYER_DIMENSION.x, Player::PLAYER_DIMENSION.y};

    playerProfile->update(*heartAmount, *sprintAmount);
}

void Player::render() {
    SDL_Rect srcRect = getSrcRectDirectionFacing();

    if (*alive) SDL_RenderCopy(Game::getInstance()->getRenderer(), textureType->texture, &srcRect, dstRectPlatform.get());   
    else SDL_RenderCopy(Game::getInstance()->getRenderer(), *deadColorTexture.get(), &srcRect, dstRectPlatform.get());
}

void Player::renderPlayerProfiles() const {
    playerProfile->render();
    textPlayerName->render();
    textPlayerPosition->render();
}

int Player::getID() const {
    return *ID;
}

std::shared_ptr<Prototype> Player::clone() const {
    return std::make_shared<Player>(*this);
}