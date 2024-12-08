#pragma once
#include <SDL.h>
#include <memory>

class Selector {
private:
    static constexpr const char* PATH = "assets/images/menuSelector.png";
    static constexpr const int SIZE_ADDER = 8;

private:
	Selector();

public:
    Selector(const Selector&) = delete;
    Selector& operator=(const Selector&) = delete;
    Selector(Selector&&) = delete;
    Selector& operator=(Selector&&) = delete;

    static Selector* getInstance();

private:
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> mTexture{ nullptr, SDL_DestroyTexture };
    SDL_Rect leftSelector;
    SDL_Rect rightSelector;
    SDL_Point dimension;
    int midDistance;
    int yDistance;

public:
    void init();

    void update(int distance, int y);
    void render();
};

