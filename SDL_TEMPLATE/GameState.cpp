#include "GameState.h"
#include "InvokerPlaying.h"
#include "Game.h"
#include "cmath"
#include "Bullet.h"
#include "Player.h"
#include "WaveManager.h"
#include "Menu.h"
#include "Minimap.h"
#include "Background.h"
#include "MenuState.h"
#include "GameSound.h"

void GameMenu::input() {
    Menu::getInstance()->input();
}

void GameMenu::update() {
    Menu::getInstance()->update();
}

void GameMenu::render() {
    Menu::getInstance()->render();
}

void GameTextInput::input() {
    Menu::getInstance()->input();
}

void GameTextInput::update() {
    Menu::getInstance()->update();
}

void GameTextInput::render() {
    Menu::getInstance()->render();
}

struct StateVector {
    float x;
    float y;
};

void GamePlaying::input() {
    switch (Game::getInstance()->getEvent().type) {
    case SDL_KEYDOWN:
        switch (Game::getInstance()->getEvent().key.keysym.sym) {
        case SDLK_LSHIFT: InvokerPlaying::getInstance()->pressButton(Command_Actions::sprint); break;
        case SDLK_a: InvokerPlaying::getInstance()->pressButton(Command_Actions::moveLeft); break;
        case SDLK_w: InvokerPlaying::getInstance()->pressButton(Command_Actions::moveUp); break;
        case SDLK_d: InvokerPlaying::getInstance()->pressButton(Command_Actions::moveRight); break;
        case SDLK_s: InvokerPlaying::getInstance()->pressButton(Command_Actions::moveDown); break;
        case SDLK_ESCAPE: 
            Game::getInstance()->setState(std::make_unique<GamePaused>());
            Menu::getInstance()->setState(std::make_unique<PausedMenu>());
            WaveManager::getInstance()->pauseCountdownTimer();
            GameSound::getInstance()->playSoundFX(SFX::minorClick);
            GameSound::getInstance()->pauseSoundFX(SFX::ticking);
            break;
        default: break;
        }
        break;
    case SDL_KEYUP:
        switch (Game::getInstance()->getEvent().key.keysym.sym) {
        case SDLK_LSHIFT: InvokerPlaying::getInstance()->pressButton(Command_Actions::unsprint); break;
        case SDLK_a: InvokerPlaying::getInstance()->pressButton(Command_Actions::keyUpMoveLeft); break;
        case SDLK_w: InvokerPlaying::getInstance()->pressButton(Command_Actions::keyUpMoveUp); break;
        case SDLK_d: InvokerPlaying::getInstance()->pressButton(Command_Actions::keyUpMoveRight); break;
        case SDLK_s: InvokerPlaying::getInstance()->pressButton(Command_Actions::keyUpMoveDown); break;
        default: break;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (Game::getInstance()->getEvent().button.button == SDL_BUTTON_LEFT) {
            InvokerPlaying::getInstance()->pressButton(Command_Actions::fire);
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (Game::getInstance()->getEvent().button.button == SDL_BUTTON_LEFT) {
            InvokerPlaying::getInstance()->pressButton(Command_Actions::unfire);
        }
        break;
    }

    {
        static Command_Actions commandAction = Command_Actions::none;
        static SDL_Point mousePos = { 0, 0 };

        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        for (auto& player : InvokerPlaying::getInstance()->players) {
            StateVector vector = {
                static_cast<float>(mousePos.x - player.second->position->x - (Player::PLAYER_DIMENSION.x / 2)),
                static_cast<float>(mousePos.y - player.second->position->y - (Player::PLAYER_DIMENSION.y / 2))
            };

            float magnitude = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));

            StateVector normalizedVector = { 0, 0 };
            if (magnitude != 0) {
                normalizedVector = { vector.x / magnitude, vector.y / magnitude };

                if (normalizedVector.x < -0.5f && normalizedVector.y > 0.5f) {
                    commandAction = Command_Actions::faceDownLeft;
                } else if (normalizedVector.x > 0.5f && normalizedVector.y > 0.5f) {
                    commandAction = Command_Actions::faceDownRight;
                } else if (normalizedVector.x < -0.5f && normalizedVector.y < -0.5f) {
                    commandAction = Command_Actions::faceUpLeft;
                } else if (normalizedVector.x > 0.5f && normalizedVector.y < -0.5f) {
                    commandAction = Command_Actions::faceUpRight;
                } else if (normalizedVector.x > 0.5f && std::abs(normalizedVector.y) <= 0.5f) {
                    commandAction = Command_Actions::faceRight;
                } else if (normalizedVector.x < -0.5f && std::abs(normalizedVector.y) <= 0.5f) {
                    commandAction = Command_Actions::faceLeft;
                } else if (normalizedVector.y > 0.5f && std::abs(normalizedVector.x) <= 0.5f) {
                    commandAction = Command_Actions::faceDown;
                } else if (normalizedVector.y < -0.5f && std::abs(normalizedVector.x) <= 0.5f) {
                    commandAction = Command_Actions::faceUp;
                }

                *player.second->directionX = normalizedVector.x;
                *player.second->directionY = normalizedVector.y;
            }
        }
        if (commandAction != Command_Actions::none) InvokerPlaying::getInstance()->pressButton(commandAction);
    }
}


void GamePlaying::update() {
    InvokerPlaying::getInstance()->updatePlayers();

    Bullet::bullets.erase(
        std::remove_if(
            Bullet::bullets.begin(),
            Bullet::bullets.end(),
            [](const std::unique_ptr<Bullet>& bullet) {
                return bullet->remove && *bullet->remove;
            }
        ),
        Bullet::bullets.end()
    );

    for (auto& bullet : Bullet::bullets) {
        bullet->update();
    }

    WaveManager::getInstance()->update();

    if (WaveManager::getInstance()->isWaveFinish()) {
        if (!WaveManager::getInstance()->hasCountdownStarted()) {
            WaveManager::getInstance()->startCountdown();
            WaveManager::getInstance()->decreasePlayersFiringCooldown();

            WaveManager::getInstance()->incrementWave();
            WaveManager::getInstance()->updateWaveCountText();
        }

        if (WaveManager::getInstance()->isCountdownFinish()) {
            WaveManager::getInstance()->setCountdownFinish();
            WaveManager::getInstance()->initWave();
        }
    }

    Minimap::getInstance()->update();
}


void GamePlaying::render() {
    Background::getInstance()->render();
    InvokerPlaying::getInstance()->renderPlayers();

    for (const auto& bullet : Bullet::bullets) {
        bullet->render();
    }

    WaveManager::getInstance()->render();
    InvokerPlaying::getInstance()->renderPlayerProfiles();
    Minimap::getInstance()->render();
}

void GamePaused::input() {
    Menu::getInstance()->input();
}

void GamePaused::update() {
    Menu::getInstance()->update();
}

void GamePaused::render() {
    GamePlaying playing;
    playing.render();

    Menu::getInstance()->render();
}

void GameOver::input() {
    Menu::getInstance()->input();
}

void GameOver::update() {
    Menu::getInstance()->update();
}

void GameOver::render() {
    GamePlaying playing;
    playing.render();

    Menu::getInstance()->render();
}