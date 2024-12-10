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

void GameSound::playMusic() {
    Mix_FadeInMusic(music, -1, 750);
}

void GameSound::stopMusic() {
    Mix_FadeOutMusic(3000);
}

void GameSound::playSoundFX(const SFX& sfx) {
    switch (sfx) {
    case SFX::click:
        Mix_PlayChannel(-1, click, 0);
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
        Mix_PlayChannel(-1, ticking, 0);
        break;
    default:
        std::cerr << "Unknown SFX!" << '\n';
        break;
    }
}
