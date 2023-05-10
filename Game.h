#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Header.h"
#include "RenderWindow.h"
#include "Menu.h"
#include "Timer.h"
#include "GameMap.h"
#include "Player.h"
#include "DarkWarrior.h"
#include "FlyingMonster.h"
#include "Boss.h"

class Game{
public:
    bool init();

    void setMap();
    void setPlayer();
    void setDarkWarrior();
    void setFlyingMonster();
    void setBoss();
    void setDynamicObject();
    void setMenu();

    bool loadImage();
    bool loadMusic();
    bool loadFont();
    bool loadMedia();
    bool isRunning();

    int getState();

    void handleStartMenuEvent(SDL_Event &event);
    void renderStartMenu();
    void handleSubMenu(SDL_Event &event);
    void renderSubMenu();
    void handleGameEvent(SDL_Event &event);
    void renderGuide();
    void handleGuideEvent(SDL_Event &event);
    void renderGame();
    void renderHP();
    void close();

private:
    RenderWindow window;
    SDL_Texture *gTexture[TOTAL_TEXTURE];
    GameMap Map;
    Tile *map_data;
    SDL_Rect camera;
    bool running;
    Player knight;
    Menu menu;
    GameState state;
    DarkWarriorFamily darkWarriors;
    FlyingMonsterFamily flyingMonsters;
    Boss boss;

    int hp;
    stringstream hpText;

    Mix_Chunk *menuSound[TOTAL_MENU_SOUND_EFFECT];
    Mix_Music *menuTheme, *gameTheme;
    TTF_Font *font[TOTAL_FONT];
};

#endif // GAME_H_INCLUDED
