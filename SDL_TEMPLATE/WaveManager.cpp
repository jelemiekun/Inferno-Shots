#include "WaveManager.h"
#include "Enemy.h"
#include "NormalEnemy.h"
#include "PrototypeRegistry.h"

std::unique_ptr<int> WaveManager::waveCount = std::make_unique<int>(0);

WaveManager::WaveManager() {}

WaveManager* WaveManager::getInstance() {
    static WaveManager instance;
    return &instance;
}

void WaveManager::initWave() {
    int enemyCount = *waveCount * WaveManager::INIT_ENEMY_COUNT;

    for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++) {
        std::shared_ptr<NormalEnemy> enemy = std::dynamic_pointer_cast<NormalEnemy>(
            PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::NORMAL_ENEMY)
        );

        enemies.push_back(enemy);
    }
}

void WaveManager::update() {
    std::vector<std::shared_ptr<Enemy>> enemiesToRemove;

    for (auto& enemy : enemies) {
        enemy->update();

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
}

const int& WaveManager::getWaveCount() const {
    return *WaveManager::waveCount;
}