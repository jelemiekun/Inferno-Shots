#pragma once
#include <unordered_map>
#include <memory>
#include "GameEnums.h"

class Prototype;

class PrototypeRegistry {
private:
	PrototypeRegistry();

public:
	PrototypeRegistry(const PrototypeRegistry&) = delete;
	PrototypeRegistry& operator=(const PrototypeRegistry&) = delete;
	PrototypeRegistry(PrototypeRegistry&&) = delete;
	PrototypeRegistry& operator=(PrototypeRegistry&&) = delete;

public:
	static PrototypeRegistry* getInstance();

private:
	std::unordered_map <Prototype_Type, std::shared_ptr<Prototype>> prototypes;

public:
	void addPrototype(Prototype_Type type, std::shared_ptr<Prototype> prototype);

	std::shared_ptr<Prototype> getPrototype(Prototype_Type type) const;
};

