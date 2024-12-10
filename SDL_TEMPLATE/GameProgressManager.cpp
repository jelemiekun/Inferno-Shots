#include "GameProgressManager.h"
#include <iostream>
#include "GameProgress.h"

GameProgressManager::GameProgressManager() : file(nullptr) {}

GameProgressManager* GameProgressManager::getInstance() {
    static GameProgressManager instance;
    return &instance;
}

void GameProgressManager::loadProgress(GameProgress& progress) {
    fopen_s(&file, FILE_PATH, "rb");

    if (!file) {
        std::cout << "Failed to open progress path." << '\n';
        return;
    } else {
        std::cout << "Progress path opened." << '\n';
    }

    size_t elements_read = fread_s(&progress, sizeof(GameProgress), sizeof(GameProgress), 1, file);

    fclose(file);

    if (elements_read == 0) {
        std::cout << "Failed to read data." << '\n';
    } else {
        std::cout << "Successfully read data." << '\n';
    }
}

void GameProgressManager::saveProgress(const GameProgress& progress) {
    fopen_s(&file, FILE_PATH, "wb");

    if (!file) {
        std::cout << "Failed to open progress path." << '\n';
        return;
    } else {
        std::cout << "Progress path opened." << '\n';
    }

    size_t elements_written = fwrite(&progress, sizeof(GameProgress), 1, file);

    fclose(file);

    if (elements_written == 0) {
        std::cout << "Failed to write data." << '\n';
    } else {
        std::cout << "Successfully write data." << '\n';
    }
}
