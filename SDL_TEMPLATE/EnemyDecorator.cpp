#include "EnemyDecorator.h"

EnemyDecorator::EnemyDecorator(std::shared_ptr<Enemy> enemy) : decoratedEnemy(enemy) {}

void EnemyDecorator::initPos() {
    decoratedEnemy->initPos();
}

int EnemyDecorator::getEnemyScore() {
    return decoratedEnemy->getEnemyScore();
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

const SDL_Point& EnemyDecorator::getDimension() const {
    return decoratedEnemy->getDimension();
}

const int EnemyDecorator::getDamage() const {
    return decoratedEnemy->getDamage();
}

void EnemyDecorator::setDead() {
    decoratedEnemy->setDead();
}

void EnemyDecorator::decreaseHealth() {
    decoratedEnemy->decreaseHealth();
}


int EnemyDecorator::getMinimapPixelSize() {
    return decoratedEnemy->getMinimapPixelSize();
}

std::shared_ptr<Prototype> EnemyDecorator::clone() const {
    return decoratedEnemy->clone();
}