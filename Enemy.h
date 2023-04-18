#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Header.h"
#include "Tile.h"
#include "RenderWindow.h"

const int MONSTER_FRAME_NUM = 39;

const int MONSTER_SPEED = 1;
const int MONSTER_GRAVITY_SPEED = 1;
const int MONSTER_MAX_FALL_SPEED = 8;

class Monster : public RenderWindow{
public:
    public:
    Monster();
    ~Monster();

    void set_x_pos(const int& xp);
//    void set_y_pos(const int& yp) {y_pos = yp;}
    void setMapXY(const int& mp_x, const int& mp_y) {map_x = mp_x; map_y = mp_y;}

    void set_clips();
    void loadMonsterTexture(RenderWindow &window);
    void show(RenderWindow &window);
    void move(SDL_Rect player_box, Tile* map_data);
    void checkToMap(Tile *map_data);

    bool touchesWall(Tile *map_data);
    bool checkCollision(SDL_Rect a, SDL_Rect b);

    //dwvector <Monster*> makeThreatList(SDL_Renderer* ren);

    void isAttacked(Input i, SDL_Rect player_box, SDL_Rect player_currentBox, int player_status);
    bool isAttacking (Input i, SDL_Rect player_box);
    void drawHP(SDL_Renderer &ren, SDL_Rect &mCamera);
    bool getDead() {return isDead;}

    SDL_Rect getBox(){return mBox;}
private:
    int HP;
    SDL_Rect mBox;
    SDL_Rect currentBox;
    SDL_Texture *mTexture;
    int mVelX, mVelY;
    //int x_pos, y_pos;
    int x_min, x_max;
    int push;

    SDL_Rect Monster_Clips[MONSTER_FRAME_NUM];
    int frame;

    bool on_ground;

    int map_x;
    int map_y;

    //vector <Monster*> threats_list;
    int status;
    Input input_type;
    bool isDead;
    Animation idle = Animation(0, 8, 96, 96, 8);
    Animation run = Animation(1, 8, 120, 96, 8, 0, 15);
    Animation attack = Animation(2, 10, 216, 144, 8, 0, 108, 48);
    Animation hurt = Animation(3, 3, 96, 96, 8);
    Animation dead = Animation(4, 10, 96, 96, 8);
    vector <Animation> animations;
};

#endif // ENEMY_H_INCLUDED

