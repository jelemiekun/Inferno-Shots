#include "EnemyDecorator.h"

EnemyDecorator::EnemyDecorator(std::shared_ptr<Enemy> enemy) : decoratedEnemy(enemy) {}

void EnemyDecorator::initPos() {
    decoratedEnemy->initPos();
}

void EnemyDecorator::inflictDamage(Player& player) {
    decoratedEnemy->inflictDamage(player);
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

const SDL_Point& EnemyDecorator::getPosition() const {
    return decoratedEnemy->getPosition();
}

std::shared_ptr<Prototype> EnemyDecorator::clone() const {
    return decoratedEnemy->clone();
}