#pragma once
#include <memory>

class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::shared_ptr<Prototype> clone() const = 0;
};
