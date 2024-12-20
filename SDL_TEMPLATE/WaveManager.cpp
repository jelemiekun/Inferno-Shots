#include "WaveManager.h"
#include "Enemy.h"
#include "EnemyType.h"
#include "PrototypeRegistry.h"
#include "CountdownTimer.h"
#include "AppInfo.h"
#include "InvokerPlaying.h"
#include "Bar.h"
#include "Text.h"
#include "FastEnemy.h"
#include "GameSound.h"
#include <random>
#include <string>

std::unique_ptr<int> WaveManager::waveCount = std::make_unique<int>(0);

std::unique_ptr<CountdownTimer> WaveManager::countdownTimer = std::make_unique<CountdownTimer>();

std::unique_ptr<Bar> WaveManager::countdownBar = std::make_unique<Bar>();

std::unique_ptr<Text> WaveManager::countdownText = std::make_unique<Text>();

std::unique_ptr<Text> WaveManager::waveCountText = std::make_unique<Text>();

std::unique_ptr<Text> WaveManager::playerScoreText = std::make_unique<Text>();

std::unique_ptr<bool> WaveManager::waveCountFromLoadFile = std::make_unique<bool>(false);

WaveManager::WaveManager() {}

SDL_Rect WaveManager::getCountdownTextDstRect() {
    SDL_Rect dstRect{ 0, 0, 300, 35 };
    dstRect.x = (SCREEN_WIDTH / 2) - (dstRect.w / 2);
    dstRect.y = SCREEN_HEIGHT - dstRect.h - 80;
    return dstRect;
}

SDL_Rect WaveManager::getWaveCountTextDstRect() {
    SDL_Rect dstRect{ 5, 0, 100, 25 };
    dstRect.y = SCREEN_HEIGHT - dstRect.h - dstRect.x - 5;
    return dstRect;
}

void WaveManager::initTexts() {
    countdownText->setFont(Font::MOTION_CONTROL_BOLD);
    countdownText->setText("Time Until Next Wave:");
    countdownText->setDstRect(getCountdownTextDstRect());
    countdownText->setColor({ 255, 255, 255, 255 });
    countdownText->loadText();

    waveCountText->setFont(Font::MOTION_CONTROL_BOLD);
    SDL_Rect waveCountTextDstRect = getWaveCountTextDstRect();
    waveCountText->setDstRect(waveCountTextDstRect);
    waveCountText->setColor({ 255, 255, 255, 255 });

    playerScoreText->setFont(Font::MOTION_CONTROL_BOLD);
    SDL_Rect playerScoreTextDstRect = waveCountTextDstRect;
    playerScoreTextDstRect.x = 14;
    playerScoreTextDstRect.y -= waveCountTextDstRect.h;
    playerScoreText->setDstRect(playerScoreTextDstRect);
    playerScoreText->setColor({ 255, 255, 255, 255 });
}

WaveManager* WaveManager::getInstance() {
    static WaveManager instance;
    return &instance;
}

Uint32 WaveManager::getCountdownDuration() const {
    Uint32 duration = 1000;

    if (*waveCount <= 6) {
        duration = 3500;
    } else if (*waveCount <= 11) {
        duration = 5000;
    } else if (*waveCount <= 20) {
        duration = 7000;
    } else {
        duration = 10000;
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

int WaveManager::getEnemyCountToinit() {
    return *waveCount * WaveManager::INIT_ENEMY_COUNT;
}

int WaveManager::getRandomNumber(const int& max) {
    int threeFourthOfMax;

    if (max <= 0) {
        threeFourthOfMax = 1;
    } else {
        threeFourthOfMax = static_cast<int>((max / 8) * 7);

        if (threeFourthOfMax <= 0) {
            threeFourthOfMax = 1;
        }
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, threeFourthOfMax);

    return dist6(rng);
}

void WaveManager::resetWaveCount() {
    if (!(*waveCountFromLoadFile)) {
        *waveCount = 0;
    } else {
        *waveCountFromLoadFile = false;
    }
}

void WaveManager::clearEnemies() {
    enemies.clear();
}

void WaveManager::resetGame() {
    resetWaveCount();
    clearEnemies();
    setCountdownFinish();
}

void WaveManager::setWaveCount(int waveCount) {
    *waveCountFromLoadFile = true;
    *WaveManager::waveCount.get() = waveCount;
}

void WaveManager::initWave() {
    GameSound::getInstance()->stopSoundFX();

    int enemyCount = getEnemyCountToinit();

    // Normal Enemies Fast
    if (*waveCount > 3) {
        int fastEnemyCount = getRandomNumber(enemyCount);

        for (int enemyIndex = 0; enemyIndex < fastEnemyCount; enemyIndex++) {
            std::shared_ptr<FastEnemy> fastNormalEnemy = std::dynamic_pointer_cast<FastEnemy>(
                PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::NORMAL_ENEMY_FAST)
            );

            fastNormalEnemy->initPos();
            enemies.push_back(fastNormalEnemy);
        }
    }

    // Medium Enemies
    if (*waveCount > 8) {
        int mediumEnemyCount = getRandomNumber(static_cast<int>(enemyCount / 2));

        for (int enemyIndex = 0; enemyIndex < mediumEnemyCount; enemyIndex++) {
            std::shared_ptr<EnemyType> mediumEnemy = std::dynamic_pointer_cast<EnemyType>(
                PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::MEDIUM_ENEMY)
            );

            mediumEnemy->initPos();
            enemies.push_back(mediumEnemy);
        }

        // Fast Medium Enemies
        if (*waveCount > 16) {
            int fastMediumEnemyCount = getRandomNumber(static_cast<int>(mediumEnemyCount / 2));

            for (int enemyIndex = 0; enemyIndex < fastMediumEnemyCount; enemyIndex++) {
                std::shared_ptr<FastEnemy> fastMediumEnemy = std::dynamic_pointer_cast<FastEnemy>(
                    PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::MEDIUM_ENEMY_FAST)
                );

                fastMediumEnemy->initPos();
                enemies.push_back(fastMediumEnemy);
            }
        }
    }

    // Large Enemies
    if (*waveCount % 5 == 0 && *waveCount > 9) {
        GameSound::getInstance()->playSoundFX(SFX::largeEnemySpawned);

        int largeEnemyCount = 1;

        std::shared_ptr<EnemyType> largeEnemy = std::dynamic_pointer_cast<EnemyType>(
            PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::LARGE_ENEMY)
        );

        largeEnemy->initPos();
        enemies.push_back(largeEnemy);
        // Fast Large Enemies
        if (*waveCount > 19) {
            int fastLargeEnemyCount = getRandomNumber(static_cast<int>(enemyCount / 10));

            for (int enemyIndex = 0; enemyIndex < fastLargeEnemyCount; enemyIndex++) {
                std::shared_ptr<FastEnemy> fastLargeEnemy = std::dynamic_pointer_cast<FastEnemy>(
                    PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::LARGE_ENEMY_FAST)
                );

                fastLargeEnemy->initPos();
                enemies.push_back(fastLargeEnemy);
            }
        }
    }

    // Normal Enemies
    for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++) {
        std::shared_ptr<EnemyType> normalEnemy = std::dynamic_pointer_cast<EnemyType>(
            PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::NORMAL_ENEMY)
        );
        normalEnemy->initPos();
        enemies.push_back(normalEnemy);
    }
    
}

void WaveManager::updateEnemies() {
    std::vector<std::shared_ptr<Enemy>> deadEnemiesToRemove;

    for (auto& enemy : enemies) {
        enemy->update();
        enemy->checkCollision();
        if (enemy->isDead()) {
            deadEnemiesToRemove.push_back(enemy);
            if (enemy->getType() == Prototype_Type::NORMAL_ENEMY || 
                enemy->getType() == Prototype_Type::NORMAL_ENEMY_FAST) {
                GameSound::getInstance()->playSoundFX(SFX::normalEnemyDead);
            } else if (enemy->getType() == Prototype_Type::MEDIUM_ENEMY ||
                enemy->getType() == Prototype_Type::MEDIUM_ENEMY_FAST) {
                GameSound::getInstance()->playSoundFX(SFX::mediumEnemyDead);
            } else if (enemy->getType() == Prototype_Type::LARGE_ENEMY ||
                enemy->getType() == Prototype_Type::LARGE_ENEMY_FAST) {
                GameSound::getInstance()->playSoundFX(SFX::largeEnemyDead);
            }
        }
    }

    removeDeadEnemies(deadEnemiesToRemove);
}

void WaveManager::updatePlayerScoreText() {
    playerScoreText->setText("Score: " + std::to_string(Player::staticScore));
    playerScoreText->loadText();
}

void WaveManager::removeDeadEnemies(const std::vector<std::shared_ptr<Enemy>>& deadEnemiesToRemove) {
    for (const auto& enemy : deadEnemiesToRemove) {
        enemies.erase(
            std::remove_if(
                enemies.begin(),
                enemies.end(),
                [&enemy](const std::shared_ptr<Enemy>& e) {
                    return e == enemy;
                }),
            enemies.end());
    }
}

void WaveManager::update() {
    updateEnemies();
    countdownBar->update(static_cast<float>(countdownTimer->getDurationTime() - countdownTimer->getElapsedTime()));
    updatePlayerScoreText();
}


void WaveManager::render() {
    for (auto& enemy : enemies) {
        enemy->render();
    }
    
    if (!isCountdownFinish()) {
        countdownText->render();
        countdownBar->render();
    }

    waveCountText->render();
    playerScoreText->render();
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
        GameSound::getInstance()->playSoundFX(SFX::ticking);
    }
}

bool WaveManager::isCountdownFinish() const {
    return countdownTimer->isFinished();
}

bool WaveManager::hasCountdownStarted() const {
    return countdownTimer->hasStarted();
}

void WaveManager::updateWaveCountText() {
    waveCountText->setText(" Wave: " +  std::to_string(*waveCount));
    waveCountText->loadText();
}

void WaveManager::setCountdownFinish() {
    countdownTimer->setFinish();
}

void WaveManager::pauseCountdownTimer() {
    countdownTimer->pause();
}

void WaveManager::unpauseCountdownTimer() {
    countdownTimer->unpause();
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