#pragma once
#include "Prototype.h"

class Enemy : public Prototype {
public:
    virtual ~Enemy() = default;
    virtual void initPos() = 0;
    virtual void update() = 0;
    virtual void render() const = 0;
    virtual const bool& isDead() const = 0;
};