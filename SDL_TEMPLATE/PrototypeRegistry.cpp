#include "PrototypeRegistry.h"
#include "Prototype.h"

PrototypeRegistry::PrototypeRegistry() {}

PrototypeRegistry* PrototypeRegistry::getInstance() {
    static PrototypeRegistry instance;
    return &instance;
}

void PrototypeRegistry::addPrototype(Prototype_Type type, std::shared_ptr<Prototype> prototype) {
	prototypes[type] = prototype;
}

std::shared_ptr<Prototype> PrototypeRegistry::getPrototype(Prototype_Type type) const {
    if (prototypes.find(type) != prototypes.end()) {
        return prototypes.at(type)->clone();
    }
    return nullptr;
}