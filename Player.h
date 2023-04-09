#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Header.h"
#include "RenderWindow.h"
#include "Tile.h"
#include "GameMap.h"
#include "Enemy.h"

const int PLAYER_SPEED = 4;
const int PLAYR_JUMP_VAL = 25;

const int SHEET_WIDTH = 1109;

const int TOTAL_FRAME = 49;

class Player : public RenderWindow
{
public:
    Player();

    enum playerType{
        NONE = 0,
        LEFT = 1,
        RIGHT = 2,
    };
    void loadPlayerTexture(RenderWindow &window);
    void show(RenderWindow &window, SDL_Rect &mCamera);
    void handleEvent( SDL_Event& event );
    void setClips();
    void doPlayer(Tile *map_data);
    void checkToMap(Tile *map_data);

    bool touchesWall(Tile *map_data);
    bool checkCollision(SDL_Rect a, SDL_Rect b);

    void centerPlayerOnMap(SDL_Rect &mCamera);

    void drawHP(SDL_Renderer &ren, SDL_Rect &mCamera);
    void isHitted(bool ok);
    bool isDead();

    SDL_Rect getBox() {return mBox;}
    Input getInputType() {return input_type;}

private:
    SDL_Rect mBox;
    Tile map_data;
    int mVelX, mVelY;
    SDL_Texture *mTexture;
    SDL_Rect m_playerClips[TOTAL_FRAME];
    int status;
    int frame;

    bool on_ground;
    Input input_type;

    int HP;

    Animation idle = Animation(0, 4, 64, 80, 16);
    Animation attack1 = Animation(1, 5, 160, 96, 8, 32, 64, 16);
    Animation attack2 = Animation(2, 4, 160, 96, 8, 32, 64, 16);
    Animation attack3 = Animation(3, 4, 160, 80, 12, 16, 64, 0);
    Animation dead = Animation(4, 6, 160, 80);
    Animation defend = Animation(5, 5, 64, 80, 8);
    Animation hurt = Animation(6, 2, 64, 80);
    Animation jump = Animation(7, 6, 128, 80, 8, 32, 32, 0);
    Animation run = Animation(8, 7, 80, 80, 12);
    Animation run_attack = Animation(9, 6, 128, 96, 12, 20, 16);
    vector <Animation> animations;
};

#endif // PLAYER_H_INCLUDED
