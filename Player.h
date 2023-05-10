#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Header.h"
#include "RenderWindow.h"
#include "Tile.h"
#include "GameMap.h"
#include "Enemy.h"

const int PLAYER_SPEED = 2;
const int PLAYR_JUMP_VAL = 28;
const int HP_MAX = 20;
const int TOTAL_PLAYER_FRAME = 49;

class Player
{
public:
    Player(SDL_Texture *p_tex = nullptr, SDL_Texture *hp_tex = nullptr);

    void loadPlayerTexture(RenderWindow &window);
    void show(RenderWindow &window, SDL_Rect &mCamera);
    void handleEvent( SDL_Event& event, GameState &state, int &hp);
    void setClips();
    void doPlayer(Tile *map_data);
    void checkToMap(Tile *map_data);

    bool touchesWall(Tile *map_data);
    bool checkCollision(SDL_Rect a, SDL_Rect b);

    void centerPlayerOnMap(SDL_Rect &mCamera);

    void drawHP(SDL_Renderer &ren, SDL_Rect &mCamera);

    void isHittingPotion(int &hp);
    void isHitted(bool hitted, int enemy_status);
    void isHittedByBullet(bool isBHitted, RenderWindow &window, SDL_Rect &mCamera);
    bool isDead();

    SDL_Rect getCurrentBox() {return currentBox;}
    SDL_Rect getBox() {return mBox;}
    Input getInputType(){return input_type;}
    int getStatus() {return status;}

private:
    SDL_Texture *mTexture, *hpTexture;
    SDL_Rect mBox;
    SDL_Rect currentBox;
    SDL_Rect m_playerClips[TOTAL_PLAYER_FRAME];
    Tile map_data;
    Input input_type;
    int status;
    int frame, eFrame;
    int direction;
    bool on_ground;
    int mVelX, mVelY;
    int HP;
    int havePotion;

    vector <SDL_Rect> potions;

    Animation idle = Animation(0, 4, 64, 80, 16);
    Animation attack1 = Animation(1, 5, 160, 96, 8, 32, 64, 16);
    Animation attack2 = Animation(2, 4, 160, 96, 8, 32, 64, 16);
    Animation attack3 = Animation(3, 4, 160, 80, 12, 16, 64, 0);
    Animation dead = Animation(4, 6, 160, 80, 36, 0, 64);
    Animation defend = Animation(5, 5, 64, 80, 8);
    Animation hurt = Animation(6, 2, 64, 80, 16);
    Animation jump = Animation(7, 6, 112, 80, 16, 16, 16, 0);
    Animation run = Animation(8, 7, 80, 80, 12);
    vector <Animation> animations;
};

#endif // PLAYER_H_INCLUDED
