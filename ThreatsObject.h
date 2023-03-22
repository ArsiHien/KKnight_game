#ifndef THREATSOBJECT_H_INCLUDED
#define THREATSOBJECT_H_INCLUDED

#include "Header.h"
#include "renderWindow.h"

#define THREAT_FRAME_NUM 8
#define THREATS_GRAVITY_SPEED 0.8
#define THREARS_MAX_FALL_SPEED 10

class ThreatsObject : public renderWindow
{
public:
    ThreatsObject();
    ~ThreatsObject();

    void set_x_val(const float& xVal) {x_val = xVal;}
    void set_y_val(const float& xVal) {x_val = xVal;}
    void set_x_pos(const float& xp) {x_pos = xp;}
    void set_y_pos(const float& yp) {y_pos = yp;}

    float get_x_pos() const {return x_pos;}
    float get_y_pos() const {return y_pos;}
    void setMapXY(const int& mp_x, const int& mp_y) {map_x = mp_x; map_y = mp_y;}

    void set_clips();
    bool loadIMG(string filePath, SDL_Renderer* ren);
    void show(SDL_Renderer* des);
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}
    void doPlayer(Map& gMap);
    void checkToMap(Map& gMap);
private:
    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[THREAT_FRAME_NUM];
    int frame;

    bool on_ground;

    int map_x;
    int map_y;
};


#endif // THREATSOBJECT_H_INCLUDED
