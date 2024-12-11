#pragma once
#include <SDL_mixer.h>

enum class SFX {
	click,
	minorClick,
	damage,
	fire,
	largeEnemySpawned,
	largeEnemyDead,
	mediumEnemyDead,
	normalEnemyDead,
	select,
	gameOver,
	ticking
};

class GameSound {
private:
	GameSound();

public:
	GameSound(const GameSound&) = delete;
	GameSound& operator=(const GameSound&) = delete;
	GameSound(GameSound&&) = delete;
	GameSound& operator=(GameSound&&) = delete;

	static GameSound* getInstance();
	int tickingChannel = -1;

private:
	Mix_Music* music;

	Mix_Chunk* click;
	Mix_Chunk* minorClick;
	Mix_Chunk* damage;
	Mix_Chunk* fire;
	Mix_Chunk* largeEnemySpawned;
	Mix_Chunk* largeEnemyDead;
	Mix_Chunk* mediumEnemyDead;
	Mix_Chunk* normalEnemyDead;
	Mix_Chunk* select;
	Mix_Chunk* gameOver;
	Mix_Chunk* ticking;

	SFX sfx;

public:
	void initMixer();
	void loadMusic();
	void loadSoundFX();
	void setAudiosVolume();
	void playMusic();
	void stopMusic();
	void playSoundFX(const SFX& sfx);
	void stopSoundFX();
	void pauseSoundFX(const SFX& sfx);
};

