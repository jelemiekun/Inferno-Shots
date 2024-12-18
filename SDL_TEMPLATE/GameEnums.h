#pragma once
#include <iostream>
#include "SDL.h"

using Dimension = SDL_Point;

constexpr int BORDER_ALLOWANCE = 12;

enum class Face_Direction {
	LEFT,
	UP_LEFT,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT
};

enum class Prototype_Type {
	PLAYER,
	BULLET,
	NORMAL_ENEMY,
	NORMAL_ENEMY_FAST,
	MEDIUM_ENEMY,
	MEDIUM_ENEMY_FAST,
	LARGE_ENEMY,
	LARGE_ENEMY_FAST
};

std::string getProtoType_Type_Path(Prototype_Type type);