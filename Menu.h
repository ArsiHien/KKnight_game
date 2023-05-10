#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Header.h"
#include "RenderWindow.h"

const int BACKGROUND_TEXTURE_WIDTH = 2560;
const int BACKGROUND_TEXTURE_HEIGHT = 1280;

const int MENU_BACKGROUND_WIDTH = 640;
const int MENU_BACKGROUND_HEIGHT = 600;
const int MENU_BACKGROUND_TEXTURE_WIDTH = 960;
const int MENU_BACKGROUND_TEXTURE_HEIGHT = 1280;

const int MENU_TITLE_WIDTH = 380;
const int MENU_TITLE_HEIGHT = 82;
const int MENU_TITLE_TEXTURE_WIDTH = 744;
const int MENU_TITLE_TEXTURE_HEIGHT = 160;

const int BUTTON_WIDTH = 180;
const int BUTTON_HEIGHT = 60;
const int BUTTON_TEXTURE_WIDTH = 480;
const int BUTTON_TEXTURE_HEIGHT = 160;

const int LONG_BUTTON_WIDTH = 240;
const int LONG_BUTTON_HEIGHT = 60;
const int LONG_BUTTON_TEXTURE_WIDTH = 960;
const int LONG_BUTTON_TEXTURE_HEIGHT = 160;

enum Background
{
    BACKGROUND_START,
    BACKGROUND_INGAME,
    TOTAL_BACKGROUND,
};

enum Title
{
    PAUSE,
    GAMEOVER,
    VICTORY,
    TOTAL_TITLE,
};

enum Button
{
    PLAY,
    GUIDE,
    QUIT1,
    HOME,
    CONTINUE,
    PLAY_AGAIN,
    QUIT2,
    TOTAL_BUTTON,
};

class Menu
{
public:
    Menu(SDL_Texture *menu_texture = nullptr, SDL_Texture *bg_texture = nullptr);
    void handleEvent(SDL_Event &e, GameState &state, Mix_Chunk *gSound[]);
    void renderBackgroundInGame(RenderWindow &window);
    void renderMenuStart(RenderWindow &window);
    void renderMenuInGame(RenderWindow &window, GameState &state);
    void renderGuide(RenderWindow &window);

private:
    SDL_Texture *mTexture;
    SDL_Texture *bgTexture;
    SDL_Rect backgroundBox, menuBackgroundBox,titleBox, buttonBox[TOTAL_BUTTON];
    SDL_Rect backgroundClip[TOTAL_BACKGROUND], menuBackgroundClip, guideClip, titleClips[TOTAL_TITLE], buttonClips[TOTAL_BUTTON][2];
    int mouseover[TOTAL_BUTTON];
    bool isLong[TOTAL_BUTTON];
};

#endif // MENU_H_INCLUDED
