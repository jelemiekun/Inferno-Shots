#pragma once
#include <SDL.h>
#include <memory>
#include <string>

class MenuState;
class Text;

struct MouseStateFlags {
    unsigned int outside : 1;
    unsigned int clicked : 1;
};

struct MainMenuFlags {
    unsigned int play : 1;
    unsigned int loadGame : 1;
    unsigned int changeName : 1;
    unsigned int exit : 1;
};

struct ChangeNameFlags {
    unsigned int change : 1;
    unsigned int cancel : 1;
};

struct PauseFlags {
    unsigned int resume : 1;
    unsigned int saveGame : 1;
    unsigned int exit : 1;
};

struct GameOverFlags {
    unsigned int playAgain : 1;
    unsigned int mainMenu : 1;
};

class Menu {

private:
    constexpr const static char* MENU_BG_PATH = "assets/images/menuBackgroundWText-Sheet.png";
    constexpr const static char* PAUSE_GO_BG_PATH = "assets/images/pauseGameOverBackground-Sheet.png";
    
public:
    constexpr static int MAX_INPUT_LENGTH = 10;
    static std::string tempPlayerNamme;
private:
	Menu();

public:
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    Menu(Menu&&) = delete;
    Menu& operator=(Menu&&) = delete;

    static Menu* getInstance();

private:
    void initTexture(
        const char* filePath,
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>& texture,
        std::unique_ptr<SDL_Point>& dimension
    );
    void initFlags();
    void initPlayerNameText();

public:
    void initPausedGameOverDstRect();
    void changePlayerName();
    void resetFlags();
    void initMenu();

public:
    std::unique_ptr<MenuState> currentState;

    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> mTextureMenu { nullptr, SDL_DestroyTexture };
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> mTexturePauseGO { nullptr, SDL_DestroyTexture };
    std::unique_ptr<SDL_Point> menuBackgroundDimension;
    std::unique_ptr<SDL_Point> pauseGODimension;

    std::unique_ptr<MouseStateFlags> mouseStateFlags;
    std::unique_ptr<MainMenuFlags> mainMenuFlags;
    std::unique_ptr<ChangeNameFlags> changeNameFlags;
    std::unique_ptr<PauseFlags> pauseFlags;
    std::unique_ptr<GameOverFlags> gameOverFlags;
    std::unique_ptr<SDL_Rect> pausedGameOverDstRect;

    std::unique_ptr<Text> playerNameText;

private:

public:
    void setState(std::unique_ptr<MenuState> state);

    void input();
    void update();
    void render();
};

