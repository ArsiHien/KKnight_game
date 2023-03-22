#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int FRAME_PER_SECOND = 60;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const string WINDOW_TITLE = "KKnight_ndh";

#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

struct Map
{
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    string file_name;
};

struct Input{
    int left;
    int right;
    int up;
    int down;
    int jump;
};

#endif // HEADER_H_INCLUDED
