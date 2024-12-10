#pragma once
#include <SDL.h>
#include <functional>

struct GameProgress;

class GameProgressManager {
private:
	GameProgressManager();

public:
	GameProgressManager(const GameProgressManager&) = delete;
	GameProgressManager& operator=(const GameProgressManager&) = delete;
	GameProgressManager(GameProgressManager&&) = delete;
	GameProgressManager& operator=(GameProgressManager&&) = delete;

private:
	static constexpr const  char* FILE_PATH = "progress.bin";
	FILE* file;

public:
	static GameProgressManager* getInstance();

public:
	void loadProgress(GameProgress& progress);
	void saveProgress(const GameProgress& progress);
};