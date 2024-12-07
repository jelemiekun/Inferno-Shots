#pragma once
#include <SDL.h>
#include <memory>

class MenuState;

class Menu {
private:
    constexpr const static char* MENU_BG_PATH = "assets/images/menuBackground.png";

private:
	Menu();

public:
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    Menu(Menu&&) = delete;
    Menu& operator=(Menu&&) = delete;

    static Menu* getInstance();
    static void initMenu();

public:
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> mTexture { nullptr, SDL_DestroyTexture };
    std::unique_ptr<MenuState> currentState;

public:
    void setState(std::unique_ptr<MenuState> state);

    void input();
    void update();
    void render();
};

