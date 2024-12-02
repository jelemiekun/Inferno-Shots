#pragma once

constexpr int SCREEN_WIDTH = 1180;
constexpr int SCREEN_HEIGHT = 720;
constexpr const char* TITLE = "Game Shooter";

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