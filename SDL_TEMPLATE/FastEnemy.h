#pragma once
#include "EnemyDecorator.h"
#include "NormalEnemy.h"

class FastEnemy : public EnemyDecorator {
private:
    constexpr static int SCORE_ADDER = 2;
    constexpr static float MOVEMENT_ENHANCE_SCALE = 3.0;
    bool enhanced = false;

public:
    FastEnemy(std::shared_ptr<Enemy> enemy) : EnemyDecorator(enemy) {}

    void enhance() {
        if (!enhanced) {
            auto normalEnemy = std::dynamic_pointer_cast<NormalEnemy>(decoratedEnemy);
            if (normalEnemy) {
                *normalEnemy->movementSpeed *= MOVEMENT_ENHANCE_SCALE;
                enhanced = true;
            }
        }
    }

    void update() override {
        enhance();
        EnemyDecorator::update();
    }

    std::shared_ptr<Prototype> clone() const override {
        auto clonedEnemy = decoratedEnemy->clone();
        return std::make_shared<FastEnemy>(std::static_pointer_cast<Enemy>(clonedEnemy));
    }

    void render() const override {
        EnemyDecorator::render();
    }

    const SDL_Point& getPosition() const override {
        return EnemyDecorator::getPosition();
    }

    int getEnemyScore() override {
        return EnemyDecorator::getEnemyScore() + SCORE_ADDER;
    }
};
