#include "WaveManager.h"
#include "Enemy.h"
#include "NormalEnemy.h"
#include "PrototypeRegistry.h"
#include "CountdownTimer.h"

std::unique_ptr<CountdownTimer> WaveManager::countdownTimer = std::make_unique<CountdownTimer>();

std::unique_ptr<int> WaveManager::waveCount = std::make_unique<int>(0);

WaveManager::WaveManager() {}

WaveManager* WaveManager::getInstance() {
    static WaveManager instance;
    return &instance;
}

Uint32 WaveManager::getCountdownDuration() const {
    Uint32 duration = 1000;

    if (*waveCount <= 3) {
        duration = 3500;
    } else if (*waveCount <= 7) {
        duration = 5500;
    } else if (*waveCount <= 10) {
        duration = 7500;
    } else {
        duration = 13000;
    }

    return duration;
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
}


void WaveManager::render() {
    for (auto& enemy : enemies) {
        enemy->render();
    }
}

bool WaveManager::isWaveFinish() const {
    return enemies.empty();
}

void WaveManager::incrementWave() {
    ++(*WaveManager::waveCount);
    std::cout << *waveCount;
}

void WaveManager::startCountdown() {
    if (*waveCount == 0) {
        countdownTimer->setFinish();
    } else {
        Uint32 duration = getCountdownDuration();
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

const int& WaveManager::getWaveCount() const {
    return *WaveManager::waveCount;
}

const std::vector<std::shared_ptr<Enemy>>& WaveManager::getEnemies() const {
    return enemies;
}