#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Header.h"
#include "RenderWindow.h"
#include "Tile.h"
#include "GameMap.h"
#include "Enemy.h"

const int PLAYER_SPEED = 3;
const int PLAYR_JUMP_VAL = 28;
const int HP_MAX = 500;
const int TOTAL_FRAME = 49;

class Player
{
public:
    Player();

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
    void isHitted(bool hitted, int enemy_status);
    bool isDead();

    SDL_Rect getCurrentBox() {return currentBox;}
    SDL_Rect getBox() {return mBox;}
    Input getInputType() {return input_type;}
    int getStatus() {return status;}

private:
    SDL_Texture *mTexture;
    SDL_Rect mBox;
    SDL_Rect currentBox;
    SDL_Rect m_playerClips[TOTAL_FRAME];

    Tile map_data;
    Input input_type;
    int status;
    int frame;
    int direction;
    bool on_ground;
    int mVelX, mVelY;
    int HP;

    Animation idle = Animation(0, 4, 64, 80, 16);
    Animation attack1 = Animation(1, 5, 160, 96, 8, 32, 64, 16);
    Animation attack2 = Animation(2, 4, 160, 96, 8, 32, 64, 16);
    Animation attack3 = Animation(3, 4, 160, 80, 12, 16, 64, 0);
    Animation dead = Animation(4, 6, 160, 80, 36, 0, 64);
    Animation defend = Animation(5, 5, 64, 80, 8);
    Animation hurt = Animation(6, 2, 64, 80, 24);
    Animation jump = Animation(7, 6, 112, 80, 16, 16, 16, 0);
    Animation run = Animation(8, 7, 80, 80, 12);
    Animation run_attack = Animation(9, 6, 128, 96, 12, 20, 16);
    vector <Animation> animations;
};

#endif // PLAYER_H_INCLUDED
