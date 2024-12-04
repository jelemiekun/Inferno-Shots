#pragma once
#include "EnemyDecorator.h"
#include "NormalEnemy.h"

class FastEnemy : public EnemyDecorator {
private:
    constexpr static float MOVEMENT_ENHANCE_SCALE = 2.5;
    std::unique_ptr<bool> enhanced;

public:
    FastEnemy(std::shared_ptr<Enemy> enemy) : EnemyDecorator(enemy),
        enhanced(std::make_unique<bool>(false)) {
    }

    void enhance() {
        auto normalEnemy = std::dynamic_pointer_cast<NormalEnemy>(decoratedEnemy);
        if (normalEnemy) {
            *normalEnemy->movementSpeed *= MOVEMENT_ENHANCE_SCALE;
        }
        *enhanced = true;
    }

    void isEnhanced() {
        if (!(*enhanced))
            enhance();
    }

    void update() override {
        isEnhanced();
        EnemyDecorator::update();
    }

    void render() const override {
        EnemyDecorator::render();
    }

    std::shared_ptr<Prototype> clone() const override {
        auto clonedEnemy = decoratedEnemy->clone();
        return std::make_shared<FastEnemy>(clonedEnemy);
    }
};