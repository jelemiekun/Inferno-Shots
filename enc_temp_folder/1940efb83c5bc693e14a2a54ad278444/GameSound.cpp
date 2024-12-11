#include "GameSound.h"
#include <iostream>

GameSound::GameSound() {}

GameSound* GameSound::getInstance() {
    static GameSound instance;
    return &instance;
}

void GameSound::initMixer() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Warning: Failed to setup music controller: " << Mix_GetError() << '\n';
    } else {
        std::cout << "SDL mixer loaded." << '\n';
    }

    loadMusic();
    loadSoundFX();
    setAudiosVolume();
}

void GameSound::loadMusic() {
	music = Mix_LoadMUS("assets/audio/Hear What They Say.mp3");

	if (music) {
		std::cout << "Loaded music." << '\n';
	} else {
		std::cout << "Failed to load music: " << Mix_GetError();
	}
}

void GameSound::loadSoundFX() {
    click = Mix_LoadWAV("assets/audio/click.wav");
    if (click) std::cout << "SFX click loaded." << '\n';
    else std::cout << "Failed to load SFX click: " << Mix_GetError() << '\n';

    minorClick = Mix_LoadWAV("assets/audio/minorClick.wav");
    if (click) std::cout << "SFX minorClick loaded." << '\n';
    else std::cout << "Failed to load SFX minorClick: " << Mix_GetError() << '\n';

    damage = Mix_LoadWAV("assets/audio/damage.wav");
    if (damage) std::cout << "SFX damage loaded." << '\n';
    else std::cout << "Failed to load SFX damage: " << Mix_GetError() << '\n';

    fire = Mix_LoadWAV("assets/audio/fire.wav");
    if (fire) std::cout << "SFX fire loaded." << '\n';
    else std::cout << "Failed to load SFX fire: " << Mix_GetError() << '\n';

    largeEnemySpawned = Mix_LoadWAV("assets/audiolargeEnemySpawned.wav");
    if (largeEnemySpawned) std::cout << "SFX largeEnemySpawned loaded." << '\n';
    else std::cout << "Failed to load SFX largeEnemySpawned: " << Mix_GetError() << '\n';

    largeEnemyDead = Mix_LoadWAV("assets/audio/largeEnemy.wav");
    if (largeEnemyDead) std::cout << "SFX largeEnemyDead loaded." << '\n';
    else std::cout << "Failed to load SFX largeEnemyDead: " << Mix_GetError() << '\n';

    mediumEnemyDead = Mix_LoadWAV("assets/audio/mediumEnemy.wav");
    if (mediumEnemyDead) std::cout << "SFX mediumEnemyDead loaded." << '\n';
    else std::cout << "Failed to load SFX mediumEnemyDead: " << Mix_GetError() << '\n';

    normalEnemyDead = Mix_LoadWAV("assets/audio/normalEnemy.wav");
    if (normalEnemyDead) std::cout << "SFX normalEnemyDead loaded." << '\n';
    else std::cout << "Failed to load SFX normalEnemyDead: " << Mix_GetError() << '\n';

    select = Mix_LoadWAV("assets/audio/select.wav");
    if (select) std::cout << "SFX select loaded." << '\n';
    else std::cout << "Failed to load SFX select: " << Mix_GetError() << '\n';

    gameOver = Mix_LoadWAV("assets/audio/gameOver.wav");
    if (gameOver) std::cout << "SFX gameOver loaded." << '\n';
    else std::cout << "Failed to load SFX gameOver: " << Mix_GetError() << '\n';

    ticking = Mix_LoadWAV("assets/audio/ticking.wav");
    if (ticking) std::cout << "SFX ticking loaded." << '\n';
    else std::cout << "Failed to load SFX ticking: " << Mix_GetError() << '\n';
}

void GameSound::setAudiosVolume() {
    Mix_VolumeMusic(60);

    Mix_VolumeChunk(click, 84);
    Mix_VolumeChunk(minorClick, 65);
    Mix_VolumeChunk(damage, 54);
    Mix_VolumeChunk(fire, 25);
    Mix_VolumeChunk(largeEnemySpawned, 60);
    Mix_VolumeChunk(largeEnemyDead, 40);
    Mix_VolumeChunk(mediumEnemyDead, 40);
    Mix_VolumeChunk(normalEnemyDead, 40);
    Mix_VolumeChunk(select, 20);
    Mix_VolumeChunk(gameOver, 10);
    Mix_VolumeChunk(ticking, 70);
}


void GameSound::playMusic() {
    Mix_FadeInMusic(music, -1, 750);
}

void GameSound::stopMusic() {
    Mix_FadeOutMusic(500);
}

void GameSound::playSoundFX(const SFX& sfx) {
    setAudiosVolume();

    switch (sfx) {
    case SFX::click:
        Mix_PlayChannel(-1, click, 0);
        break;
    case SFX::minorClick:
        Mix_PlayChannel(-1, minorClick, 0);
        break;
    case SFX::damage:
        Mix_PlayChannel(-1, damage, 0);
        break;
    case SFX::fire:
        Mix_PlayChannel(-1, fire, 0);
        break;
    case SFX::largeEnemySpawned:
        Mix_PlayChannel(-1, largeEnemySpawned, 0);
        break;
    case SFX::largeEnemyDead:
        Mix_PlayChannel(-1, largeEnemyDead, 0);
        break;
    case SFX::mediumEnemyDead:
        Mix_PlayChannel(-1, mediumEnemyDead, 0);
        break;
    case SFX::normalEnemyDead:
        Mix_PlayChannel(-1, normalEnemyDead, 0);
        break;
    case SFX::select:
        Mix_PlayChannel(-1, select, 0);
        break;
    case SFX::gameOver:
        Mix_PlayChannel(-1, gameOver, 0);
        break;
    case SFX::ticking:
        tickingChannel = Mix_PlayChannel(-1, ticking, -1);
        break;
    default:
        std::cerr << "Unknown SFX!" << '\n';
        break;
    }
}

void GameSound::stopSoundFX() {
    if (tickingChannel != -1) {
        Mix_HaltChannel(tickingChannel);
        tickingChannel = -1;
    }
}

void GameSound::pauseSoundFX(const SFX& sfx) {
    if (sfx == SFX::ticking && tickingChannel != -1) {
        if (Mix_Playing(tickingChannel) && !Mix_Paused(tickingChannel)) {
            // Pause the ticking sound
            Mix_Pause(tickingChannel);
        } else if (Mix_Paused(tickingChannel)) {
            // Resume the ticking sound
            Mix_Resume(tickingChannel);
        }
    }
}
