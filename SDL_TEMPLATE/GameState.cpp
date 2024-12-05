#include "GameState.h"
#include "InvokerPlaying.h"
#include "Game.h"
#include "cmath"
#include "Bullet.h"
#include "Player.h"
#include "WaveManager.h"

struct StateVector {
    float x;
    float y;
};

void GamePlaying::input() {
    static SDL_Keycode keyCode = SDLK_KP_000;
    static SDL_Point mousePos = { 0, 0 };

    switch (Game::getInstance()->getEvent().type) {
    case SDL_KEYDOWN:
        keyCode = Game::getInstance()->getEvent().key.keysym.sym;
        if (keyCode != SDLK_KP_000) InvokerPlaying::getInstance()->pressButton(keyCode);
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (Game::getInstance()->getEvent().button.button == SDL_BUTTON_LEFT) {
            keyCode = SDLK_x; InvokerPlaying::getInstance()->pressButton(keyCode);
        }
        break;
    case SDL_KEYUP:
        switch (Game::getInstance()->getEvent().key.keysym.sym) {
        case SDLK_LSHIFT: keyCode = SDLK_CAPSLOCK; InvokerPlaying::getInstance()->pressButton(keyCode);
        case SDLK_a: keyCode = SDLK_j; InvokerPlaying::getInstance()->pressButton(keyCode);
        case SDLK_w: keyCode = SDLK_i; InvokerPlaying::getInstance()->pressButton(keyCode);
        case SDLK_d: keyCode = SDLK_l; InvokerPlaying::getInstance()->pressButton(keyCode);
        case SDLK_s: keyCode = SDLK_k; InvokerPlaying::getInstance()->pressButton(keyCode);
        default: break;
        }
        break;
    }

    {
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
                    keyCode = SDLK_v;
                } else if (normalizedVector.x > 0.5f && normalizedVector.y > 0.5f) {
                    keyCode = SDLK_n;
                } else if (normalizedVector.x < -0.5f && normalizedVector.y < -0.5f) {
                    keyCode = SDLK_r;
                } else if (normalizedVector.x > 0.5f && normalizedVector.y < -0.5f) {
                    keyCode = SDLK_y;
                } else if (normalizedVector.x > 0.0f && std::abs(normalizedVector.y) <= 0.5f) {
                    keyCode = SDLK_h;
                } else if (normalizedVector.x < 0.0f && std::abs(normalizedVector.y) <= 0.5f) {
                    keyCode = SDLK_f;
                } else if (normalizedVector.y > 0.0f && std::abs(normalizedVector.x) <= 0.5f) {
                    keyCode = SDLK_b;
                } else if (normalizedVector.y < 0.0f && std::abs(normalizedVector.x) <= 0.5f) { keyCode = SDLK_t; }

                *player.second->directionX = normalizedVector.x;
                *player.second->directionY = normalizedVector.y;
            }
        }
        if (keyCode != SDLK_KP_000) InvokerPlaying::getInstance()->pressButton(keyCode);
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
        if (!WaveManager::getInstance()->hasCountdownStarted())
            WaveManager::getInstance()->startCountdown();

        if (WaveManager::getInstance()->isCountdownFinish()) {
            WaveManager::getInstance()->setCountdownFinish();
            WaveManager::getInstance()->incrementWave();
            WaveManager::getInstance()->initWave();
        }
    }
}


void GamePlaying::render() {
    InvokerPlaying::getInstance()->renderPlayers();

    for (const auto& bullet : Bullet::bullets) {
        bullet->render();
    }

    WaveManager::getInstance()->render();

    InvokerPlaying::getInstance()->renderPlayerProfiles();
}

void GamePaused::input() {

}

void GamePaused::update() {

}

void GamePaused::render() {

}

void GameOver::input() {

}

void GameOver::update() {

}

void GameOver::render() {

}