#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const string WINDOW_TITLE = "KKnight_ndh";

const int TILE_SIZE = 16;

const int LEVEL_WIDTH = 460*16;
const int LEVEL_HEIGHT = 80*16;

const int TOTAL_TILES = 80*460;
const int TOTAL_TILE_SPRITES = 63*65;
const int TILE_FILE_SIZE = 1024;
const int ENEMY_TILE_TYPE = 2193;

const int GRAVITY_SPEED = 1;
const int MAX_FALL_SPEED = 7;

const int SCREEN_FPS = 120;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

enum StatusType
{
    NONE = 0,
    LEFT = 1,
    RIGHT = 2,
};

enum TextureID
{
    BACKGROUND_TEXTURE,
    MENU_TEXTURE,
    MAP_TEXTURE,
    PLAYER_TEXTURE,
    DARK_WARRIOR_TEXTURE,
    FLYING_MONSTER_TEXTURE,
    BULLET_TEXTURE,
    EXPLOSION_TEXTURE,
    BOSS_TEXTURE,
    POTION_TEXTURE,
    TOTAL_TEXTURE,
};

enum GameState
{
    STATE_PLAY,
    STATE_AGAIN,
    STATE_CONTINUE,
    STATE_QUIT,
    STATE_GUIDE,
    STATE_START_MENU,
    STATE_PAUSE_MENU,
    STATE_GAME_OVER_MENU,
    STATE_WIN_MENU,
    TOTAL_STATE
};

enum MenuSoundEffect{
    SELECT_BUTTON_SOUND,
    TOTAL_MENU_SOUND_EFFECT
};

enum Font
{
    FONT_16,
    FONT_32,
    TOTAL_FONT
};

struct Input
{
    Input()
    {
        left = 0;
        right = 0;
        defend = 0;
        jump = 0;
        attack = 0;
        attack1 = 0;
        attack2 = 0;
        attack3 = 0;
        hurt = 0;
        dead = 0;
        idle = 0;
        run = 0;
        skills1 = 0;
        skills2 = 0;
    }
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
    int skills1;
    int skills2;
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
