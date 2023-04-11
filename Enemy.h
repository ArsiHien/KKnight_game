#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Header.h"
#include "Tile.h"
#include "RenderWindow.h"
#include "Player.h"

const int MONSTER_FRAME_NUM = 8;
const int MONSTER_GRAVITY_SPEED = 1;
const int MONSTER_MAX_FALL_SPEED = 8;

const int MONSTER_WIDTH = 60;
const int MONSTER_HEIGHT = 60;

class Monster : public RenderWindow{
public:
    public:
    Monster();
    ~Monster();

//    void set_x_val(const int& xVal) {x_val = xVal;}
//    void set_y_val(const int& xVal) {x_val = xVal;}
    void set_x_pos(const int& xp) {x_pos = xp;}
    void set_y_pos(const int& yp) {y_pos = yp;}
//
//    int get_x_pos() const {return x_pos;}
//    int get_y_pos() const {return y_pos;}
    void setMapXY(const int& mp_x, const int& mp_y) {map_x = mp_x; map_y = mp_y;}

    void set_clips();
    void loadMonsterTexture(RenderWindow &window);
    void show(RenderWindow &window);
//    int get_width_frame() const {return width_frame;}
//    int get_height_frame() const {return height_frame;}
    void doPlayer(Tile *map_data);
    void checkToMap(Tile *map_data);

    bool touchesWall(Tile *map_data);
    bool checkCollision(SDL_Rect b);

    vector <Monster*> makeThreatList(SDL_Renderer* ren);

    void isAttacked(Input i, SDL_Rect box, SDL_Rect currentBox, int status);
    bool isAttacking (Input i, SDL_Rect box, int status);
    int getHP() {return HP;}

    SDL_Rect getBox(){return mBox;}
private:
    int HP;
    SDL_Rect mBox;
    SDL_Texture *mTexture;
    int mVelX;
    int mVelY;

    int x_pos;
    int y_pos;

    SDL_Rect frame_clip[MONSTER_FRAME_NUM];
    int frame;

    bool on_ground;

    int map_x;
    int map_y;

    vector <Monster*> threats_list;
};

#endif // ENEMY_H_INCLUDED

