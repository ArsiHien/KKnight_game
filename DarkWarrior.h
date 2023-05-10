#ifndef DARKWARRIOR_H_INCLUDED
#define DARKWARRIOR_H_INCLUDED

#include "Header.h"
#include "Tile.h"
#include "RenderWindow.h"

const int DARK_WARRIOR_FRAME_NUM = 55;

const int DARK_WARRIOR_SPEED = 1;
const int DARK_WARRIOR_GRAVITY_SPEED = 1;
const int DARK_WARRIOR_MAX_FALL_SPEED = 8;

class DarkWarrior {
public:
    DarkWarrior(int xp = 0,int yp = 0, SDL_Texture *p_texture = nullptr);
    ~DarkWarrior();

    void setMapXY(const int& mp_x, const int& mp_y) {map_x = mp_x; map_y = mp_y;}

    void set_clips();
    void show(RenderWindow &window);
    void move(const SDL_Rect &player_box, Tile* map_data);
    void checkToMap(Tile *map_data);

    bool touchesWall(Tile *map_data);
    bool checkCollision(SDL_Rect a, SDL_Rect b);


    void isAttacked(const Input &input, const SDL_Rect &player_box, const SDL_Rect &player_currentBox, const int &player_status);
    bool isAttacking (const Input &input, SDL_Rect player_box);
    void drawHP(SDL_Renderer &ren, SDL_Rect &mCamera);
    bool getDead() {return isDead;}
    int getStatus() {return status;}

    SDL_Rect getBox(){return mBox;}
private:
    int HP;
    SDL_Rect mBox, currentBox;
    SDL_Texture *mTexture;
    int mVelX, mVelY;
    int x_min, x_max;

    SDL_Rect mClips[DARK_WARRIOR_FRAME_NUM];
    int frame;

    bool on_ground;

    int map_x;
    int map_y;
    int thinkTime;
    bool hitting;

    int status;
    Input input_type;
    bool isDead;
    Animation idle = Animation(0, 9, 96, 96, 8);
    Animation run = Animation(1, 6, 96, 96, 8);
    Animation attack = Animation(2, 12, 128, 128, 8, 0, 32, 16);
    Animation hurt = Animation(3, 5, 96, 96, 8);
    Animation dead = Animation(4, 23, 144, 144, 12, 16, 16, 16);
    vector <Animation> animations;
};

class DarkWarriorFamily{
public:
    DarkWarriorFamily(SDL_Texture *p_texture = nullptr);
    void show(RenderWindow &window, SDL_Rect &mCamera);
    void move(const SDL_Rect &player_box, Tile* map_data);
    bool isAttack(const Input &input, const SDL_Rect &player_box, const SDL_Rect &player_currentBox, const int &player_status);
    void checkDied();
    bool isWin();

private:
    vector <DarkWarrior> darkWarriors;
    int cntDarkWarriorDied;
};

#endif // DARKWARRIOR_H_INCLUDED

