#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const string WINDOW_TITLE = "KKnight_ndh";

const int TILE_SIZE = 16;

const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 640;

const int TOTAL_TILES = 4000;
const int TOTAL_TILE_SPRITES = 63*65;
const int TILE_FILE_SIZE = 1024;

const int GRAVITY_SPEED = 1;
const int MAX_FALL_SPEED = 5;

enum playerType
{
    NONE = 0,
    LEFT = 1,
    RIGHT = 2,
};

struct Input
{
    int left;
    int right;
    int defend;
    int jump;
    int attack;
    int attack1;
    int attack2;
    int attack3;
    int hurt;
    int dead;
    int idle;
    int run;
    int run_attack;
};

struct Animation
{
    int index;
    int amount_of_frame;
    int frame_width;
    int frame_height;
    int slow_down;
    int denta_x_right;
    int denta_x_left;
    int denta_y;

    Animation(int i = 0, int aof = 0, int fw = 0, int fh = 0, int sd = 1, int dxr = 0, int dxl = 0, int dy = 0)
    {
        index = i;
        amount_of_frame = aof;
        frame_width = fw;
        frame_height = fh;
        slow_down = sd;
        denta_x_right = dxr;
        denta_x_left = dxl;
        denta_y = dy;
    }
};

#endif // HEADER_H_INCLUDED
