#pragma once
#include "Enemy.h"

class EnemyDecorator : public Enemy {
protected:
    std::shared_ptr<Enemy> decoratedEnemy;

public:
    EnemyDecorator(std::shared_ptr<Enemy> enemy);
    virtual void initPos() override;
    virtual int getEnemyScore() override;
    virtual void undoMove() override;
    virtual void checkCollision() override;
    virtual void update() override;
    virtual void render() const override;
    virtual const bool& isDead() const override;
    virtual const SDL_Point& getPosition() const override;
    virtual const SDL_Point& getDimension() const override;
    virtual const int getDamage() const override;
    virtual void setDead() override;
    virtual void decreaseHealth() override;
    virtual Prototype_Type getType() const override;
    virtual int getMinimapPixelSize() override;
    virtual std::shared_ptr<Prototype> clone() const override;
};
