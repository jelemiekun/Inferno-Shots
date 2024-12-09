#pragma once
#include "SDL.h"
#include <memory>
#include <vector>

class Enemy;
class CountdownTimer;
class Bar;
class Text;

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
    constexpr static int PLAYER_FIRING_COOLDOWN_DECREASER = 65;
    constexpr static int PLAYER_FIRING_COOLDOWN_LIMIT = 60;
    constexpr static int INIT_ENEMY_COUNT = 4;
    constexpr static int COUNTDOWN_BAR_BORDER_THICK = 3;
    constexpr static SDL_Color COUNTDOWN_BAR_PROGRESS_COLOR = { 181, 0, 0, 255 };
    static std::unique_ptr<int> waveCount;
    static std::unique_ptr<CountdownTimer> countdownTimer;
    static std::unique_ptr<Bar> countdownBar;
    static std::unique_ptr<Text> countdownText;
    std::vector<std::shared_ptr<Enemy>> enemies;

public:
    static SDL_Rect getTextDstRect();
    static void initTexts();

private:
    Uint32 getCountdownDuration() const;
    void setCountdownMaxAmount(Uint32 duration);
    void updateEnemies();
    void removeDeadEnemies(const std::vector<std::shared_ptr<Enemy>>& enemiesToRemove);
    int getEnemyCountToinit();
    int getRandomNumber(const int& max);
    void resetWaveCount();
    void clearEnemies();

public:
    void initCountdownBar();

    void resetGame();

    void initWave();
    void update();
    void render();

    bool isWaveFinish() const;
    void incrementWave();

    void startCountdown();
    bool isCountdownFinish() const;
    bool hasCountdownStarted() const;
    void setCountdownFinish();

    void decreasePlayersFiringCooldown();

    const int& getWaveCount() const;
    const std::vector<std::shared_ptr<Enemy>>& getEnemies() const;
};

