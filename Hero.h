#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include "Header.h"
#include "renderWindow.h"
#include "danBan.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYR_JUMP_VAL 20


class Hero : public renderWindow{
public:
    Hero();
    ~Hero();

    enum walkType{
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };

    bool loadIMG(const string filePath, SDL_Renderer* ren);
    void show(SDL_Renderer* des);
    void handelInputAction(SDL_Event event, SDL_Renderer* ren);
    void setClips();
    void doPlayer(Map& map_data);
    void checkToMap(Map& map_data);
    void setMapXY(const int _map_x, const int _map_y) {map_x = _map_x; map_y = _map_y;};
    void centerEntityOnMap(Map& map_data);
    void updateImagePlayer(SDL_Renderer* des);

    void set_luong_dan(vector <danBan*> luong_dan) {p_luong_dan = luong_dan;}
    vector <danBan*> get_luong_dan() const {return p_luong_dan;}
    void handleDan(SDL_Renderer* des);

private:
    vector <danBan*> p_luong_dan;

    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[8];
    Input input_type;
    int frame;
    int status;

    bool on_ground;

    int map_x;
    int map_y;

    int come_back_time;
};

#endif // HERO_H_INCLUDED
