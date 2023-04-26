#ifndef FLYINGMONSTER_H_INCLUDED
#define FLYINGMONSTER_H_INCLUDED

#include "Header.h"
#include "Tile.h"
#include "RenderWindow.h"

const int FMONSTER_FRAME_NUM = 40;

const int FMONSTER_SPEED = 1;
const int FMONSTER_GRAVITY_SPEED = 1;
const int FMONSTER_MAX_FALL_SPEED = 8;
const int FMAX_MONSTER_ATTACK = 3;
const int FMAX_MONSTER_DELAY = 120;

class FlyingMonster {
public:
    public:
    FlyingMonster();
    ~FlyingMonster();

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

    //dwvector <FlyingMonster*> makeThreatList(SDL_Renderer* ren);

    void isAttacked(Input i, SDL_Rect player_box, SDL_Rect player_currentBox, int player_status);
    bool isAttacking (Input i, SDL_Rect player_box);
    void drawHP(SDL_Renderer &ren, SDL_Rect &mCamera);
    bool getDead() {return isDead;}
    int getStatus() {return status;}

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

    SDL_Rect Monster_Clips[FMONSTER_FRAME_NUM];
    int frame;

    bool on_ground;

    int map_x;
    int map_y;
    int cntAttacking;
    int delay;

    //vector <Monster*> threats_list;
    int status;
    Input input_type;
    bool isDead;
    Animation idle = Animation(0, 8, 96, 96);
    Animation run = Animation(1, 7, 96, 96);
    Animation attack = Animation(2, 10, 96, 96);
    Animation dead = Animation(3, 11, 96, 96);
    Animation hurt = Animation(4, 4, 96, 96);
    vector <Animation> animations;
};

#endif // FLYINGMONSTER_H_INCLUDED
