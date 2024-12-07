#include "WaveManager.h"
#include "Enemy.h"
#include "NormalEnemy.h"
#include "PrototypeRegistry.h"
#include "CountdownTimer.h"
#include "AppInfo.h"
#include "InvokerPlaying.h"
#include "Bar.h"
#include "Text.h"
#include "FastEnemy.h"

std::unique_ptr<int> WaveManager::waveCount = std::make_unique<int>(0);

std::unique_ptr<CountdownTimer> WaveManager::countdownTimer = std::make_unique<CountdownTimer>();

std::unique_ptr<Bar> WaveManager::countdownBar = std::make_unique<Bar>();

std::unique_ptr<Text> WaveManager::countdownText = std::make_unique<Text>();


WaveManager::WaveManager() {}

SDL_Rect WaveManager::getTextDstRect() {
    SDL_Rect dstRect{ 0, 0, 300, 35 };
    dstRect.x = (SCREEN_WIDTH / 2) - (dstRect.w / 2);
    dstRect.y = SCREEN_HEIGHT - dstRect.h - 80;
    return dstRect;
}

void WaveManager::initTexts() {
    countdownText->setFont(Font::MOTION_CONTROL_BOLD);
    countdownText->setText("Time Until Next Wave:");
    countdownText->setDstRect(getTextDstRect());
    countdownText->setColor({ 255, 255, 255, 255 });
    countdownText->loadText();
}

WaveManager* WaveManager::getInstance() {
    static WaveManager instance;
    return &instance;
}

Uint32 WaveManager::getCountdownDuration() const {
    Uint32 duration = 1000;

    if (*waveCount <= 3) {
        duration = 3500;
    } else if (*waveCount <= 7) {
        duration = 4500;
    } else if (*waveCount <= 10) {
        duration = 6500;
    } else {
        duration = 9000;
    }

    return duration;
}

void WaveManager::setCountdownMaxAmount(Uint32 duration) {
    float maxAmount = static_cast<float>(duration);
    countdownBar->setMaxAmount(maxAmount);
}

void WaveManager::initCountdownBar() {
    constexpr static int Y_ALLOWANCE = 30;
    static SDL_Rect dstRect = { 0, 0, 500, 40 };
    dstRect.x = (SCREEN_WIDTH / 2) - (dstRect.w / 2);
    dstRect.y = SCREEN_HEIGHT - dstRect.h - Y_ALLOWANCE;
    countdownBar->setDstRect(dstRect);
    countdownBar->setBorderThick(COUNTDOWN_BAR_BORDER_THICK);
    countdownBar->setProgressBarColor(COUNTDOWN_BAR_PROGRESS_COLOR);
}

void WaveManager::initWave() {
    int enemyCount = *waveCount * WaveManager::INIT_ENEMY_COUNT;

    for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++) {
        std::shared_ptr<NormalEnemy> enemy = std::dynamic_pointer_cast<NormalEnemy>(
            PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::NORMAL_ENEMY)
        );
        enemy->initPos();
        enemies.push_back(enemy);
    }
    std::shared_ptr<FastEnemy> fastEnemy = std::dynamic_pointer_cast<FastEnemy>(
        PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::NORMAL_ENEMY_FAST)
    );

    fastEnemy->initPos();
    enemies.push_back(fastEnemy);
}

void WaveManager::update() {
    std::vector<std::shared_ptr<Enemy>> enemiesToRemove;

    for (auto& enemy : enemies) {
        enemy->update();

        enemy->checkCollision();

        if (enemy->isDead()) {
            enemiesToRemove.push_back(enemy);
        }
    }

    for (const auto& enemy : enemiesToRemove) {
        enemies.erase(
            std::remove_if(
                enemies.begin(),
                enemies.end(),
                [&enemy](const std::shared_ptr<Enemy>& e) {
                    return e == enemy;
                }),
            enemies.end());
    }

    countdownBar->update(static_cast<float>(countdownTimer->getDurationTime() - countdownTimer->getElapsedTime()));
}


void WaveManager::render() {
    for (auto& enemy : enemies) {
        enemy->render();
    }
    
    if (!isCountdownFinish()) {
        countdownText->render();
        countdownBar->render();
    }
}

bool WaveManager::isWaveFinish() const {
    return enemies.empty();
}

void WaveManager::incrementWave() {
    ++(*WaveManager::waveCount);
}

void WaveManager::startCountdown() {
    if (*waveCount == 0) {
        countdownTimer->setFinish();
    } else {
        Uint32 duration = getCountdownDuration();
        setCountdownMaxAmount(duration);
        countdownTimer->setDuration(duration);
        countdownTimer->start();
    }
}

bool WaveManager::isCountdownFinish() const {
    return countdownTimer->isFinished();
}

bool WaveManager::hasCountdownStarted() const {
    return countdownTimer->hasStarted();
}

void WaveManager::setCountdownFinish() {
    countdownTimer->setFinish();
}

void WaveManager::decreasePlayersFiringCooldown() {
    for (auto& player : InvokerPlaying::getInstance()->players) {
        if (*player.second->firingCooldown > PLAYER_FIRING_COOLDOWN_DECREASER + PLAYER_FIRING_COOLDOWN_LIMIT) {
            *player.second->firingCooldown -= PLAYER_FIRING_COOLDOWN_DECREASER;
        } else {
            *player.second->firingCooldown = PLAYER_FIRING_COOLDOWN_LIMIT;
        }
    }
}


const int& WaveManager::getWaveCount() const {
    return *WaveManager::waveCount;
}

const std::vector<std::shared_ptr<Enemy>>& WaveManager::getEnemies() const {
    return enemies;
}