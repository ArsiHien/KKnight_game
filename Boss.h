#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include "Header.h"
#include "Tile.h"
#include "RenderWindow.h"

const int BOSS_FRAME_NUM = 64;

const int BOSS_SPEED = 1;
const int BOSS_GRAVITY_SPEED = 1;
const int BOSS_MAX_FALL_SPEED = 8;
const int MAX_BOSS_ATTACK = 3;
const int MAX_BOSS_DELAY = 120;

class Boss {
public:
    Boss(const int &xp = 0,const int &yp = 0, SDL_Texture *p_texture = nullptr);
    ~Boss();

    void setMapXY(const int& mp_x, const int& mp_y) {map_x = mp_x; map_y = mp_y;}

    void set_clips();
    void show(RenderWindow &window, SDL_Rect player_box);
    void move(const SDL_Rect &player_box, Tile* map_data);
    void checkToMap(Tile *map_data);

    bool touchesWall(Tile *map_data);
    bool checkCollision(SDL_Rect a, SDL_Rect b);

    void isAttacked(const Input &input, const SDL_Rect &player_box, const SDL_Rect &player_currentBox, const int &player_status);
    bool isAttacking (const Input &input, SDL_Rect player_box);
    bool isAttacking2(const Input &input, SDL_Rect player_box);
    void showSkillBoss(RenderWindow &window, SDL_Rect player_box, SDL_Rect mCamera);
    void drawHP(SDL_Renderer &ren, SDL_Rect &mCamera);
    bool getDead() {return isDead;}
    int getStatus() {return status;}

    SDL_Rect getBox(){return mBox;}
private:
    int HP;
    SDL_Rect mBox, currentBox, Attack_box, rPlayerBox;
    SDL_Texture *mTexture;
    int mVelX, mVelY;
    int x_min, x_max;
    SDL_Rect Boss_Clips[BOSS_FRAME_NUM];
    int frame, sFrame;

    bool on_ground;

    int map_x;
    int map_y;
    int thinkTime;
    int skillTime;
    bool hitting, skillHitting;

    int status;
    Input input_type;
    bool isDead;
    Animation idle = Animation(0, 8, 256, 256, 16);
    Animation run = Animation(1, 8, 320, 256, 8, 0, 15);
    Animation attack = Animation(2, 10, 576, 384, 8, 0, 280, 128);
    Animation hurt = Animation(3, 3, 256, 256, 8);
    Animation dead = Animation(4, 10, 256, 256, 8);
    Animation cast = Animation(5, 9, 256, 384, 16, -32, 32, 128);
    Animation spell = Animation(6, 16, 256, 240, 8);
    vector <Animation> animations;
};

#endif // BOSS_H_INCLUDED
