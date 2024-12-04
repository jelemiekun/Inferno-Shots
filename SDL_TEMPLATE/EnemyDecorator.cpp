#include "EnemyDecorator.h"

EnemyDecorator::EnemyDecorator(std::shared_ptr<Enemy> enemy) : decoratedEnemy(enemy) {}

void EnemyDecorator::initPos() {
    decoratedEnemy->initPos();
}

void EnemyDecorator::undoMove() {
    decoratedEnemy->undoMove();
}

void EnemyDecorator::checkCollision() {
    decoratedEnemy->checkCollision();
}

void EnemyDecorator::update() {
    decoratedEnemy->update();
}
void EnemyDecorator::render() const {
    decoratedEnemy->render();
}
const bool& EnemyDecorator::isDead() const {
    return decoratedEnemy->isDead();
}

std::shared_ptr<Prototype> EnemyDecorator::clone() const {
    return decoratedEnemy->clone();
}