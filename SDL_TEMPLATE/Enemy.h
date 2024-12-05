#pragma once
#include <SDL.h>
#include "Prototype.h"

class Enemy : public Prototype {
public:
    virtual ~Enemy() = default;
    virtual void undoMove() = 0;
    virtual void checkCollision() = 0;
    virtual void initPos() = 0;
    virtual void update() = 0;
    virtual void render() const = 0;
    virtual const bool& isDead() const = 0;
    virtual const SDL_Point& getPosition() const = 0;
};