#pragma once
#include <SDL.h>

struct GameProgress {
	char playerName[10];
	int waveCount;
	int score;
	// Uint32 timePlaying; TODO : add timeplaying
};