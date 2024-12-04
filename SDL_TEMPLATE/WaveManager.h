#pragma once
#include <memory>
#include <vector>

class Enemy;

class WaveManager {
private:
    WaveManager();

public:
    WaveManager(const WaveManager&) = delete;
    WaveManager& operator=(const WaveManager&) = delete;
    WaveManager(WaveManager&&) = delete;
    WaveManager& operator=(WaveManager&&) = delete;

    static WaveManager* getInstance();

private:
    constexpr static int INIT_ENEMY_COUNT = 5;
    static std::unique_ptr<int> waveCount;

private:
    std::vector<std::shared_ptr<Enemy>> enemies;

public:
    void initWave();
    void update();
    void render();

    bool isWaveFinish() const;
    void incrementWave();

    const int& getWaveCount() const;
};

