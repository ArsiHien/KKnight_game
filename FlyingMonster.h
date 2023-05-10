#ifndef FLYINGMONSTER_H_INCLUDED
#define FLYINGMONSTER_H_INCLUDED

#include "Header.h"
#include "Tile.h"
#include "RenderWindow.h"

const int FMONSTER_FRAME_NUM = 42;

const int FMONSTER_SPEED = 1;
const int FMONSTER_GRAVITY_SPEED = 1;
const int FMONSTER_MAX_FALL_SPEED = 8;
const int FMAX_MONSTER_ATTACK = 3;
const int FMAX_MONSTER_DELAY = 120;

const int BULLET_FRAMES = 4;
const int BULLET_TEXTURE_HEIGHT = 160;
const int BULLET_TEXTURE_WIDTH = 480;
const int BULLET_HEIGHT = 20;
const int BULLET_WIDTH = 60;

const int TOTAL_EXPLOSION_FRAME = 16;
const int EXPLOSION_TEXTURE_HEIGHT = 360;
const int EXPLOSION_TEXTURE_WIDTH = 360;
const int EXPLOSION_HEIGHT = 36;
const int EXPLOSION_WIDTH = 36;

class Bullet
{
public:
    Bullet(const int &x = 0, const int &y = 0, SDL_Texture *p_texture = nullptr, SDL_Texture *e_tex = nullptr, const int &monster_status = 0);
    void setClips();
    void render(RenderWindow &window);
    void handleMove(SDL_Rect &mCamera);
    bool isHitting(Input i, SDL_Rect player_box, SDL_Rect &mCamera, int player_status);
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    SDL_Rect getBox() const
    {
        return mBox;
    }
    int getLife() const
    {
        return life;
    }
    int getStatus() const
    {
        return mStatus;
    }


private:
    float xp;
    float mVelX;
    SDL_Rect firstTouch;
    SDL_Rect rPlayerBox;
    SDL_Rect mBox, rBox;
    SDL_Rect mClips[BULLET_FRAMES];
    SDL_Rect m_explosionClips[TOTAL_EXPLOSION_FRAME];
    int frame, eFrame;
    int life;
    bool hitting;
    int mStatus;
    SDL_Texture *mTexture, *eTexture;
};

class FlyingMonster
{
public:
public:
    FlyingMonster(const int &xp = 0,const int &yp = 0, SDL_Texture *p_texture = nullptr, SDL_Texture *b_texture = nullptr,SDL_Texture *e_texture = nullptr);
    ~FlyingMonster();

    void set_x_pos(const int& xp);
    void setMapXY(const int& mp_x, const int& mp_y)
    {
        map_x = mp_x;
        map_y = mp_y;
    }

    void set_clips();
    void loadMonsterTexture(RenderWindow &window);
    void show(RenderWindow &window, SDL_Rect &mCamera, const Input &input, const SDL_Rect &player_box, int player_status, GameState &state);
    void move(const SDL_Rect &player_box, Tile* map_data);
    void checkToMap(Tile *map_data);

    bool touchesWall(Tile *map_data);
    bool checkCollision(SDL_Rect a, SDL_Rect b);

    void isAttacked(Input i, SDL_Rect player_box, SDL_Rect player_currentBox, int player_status);
    bool isAttacking (const Input &i, const SDL_Rect &player_box);
    void drawHP(SDL_Renderer &ren, SDL_Rect &mCamera);

    void handleBullets(RenderWindow &window, SDL_Rect &mCamera, const int &monster_status, const Input &input, const SDL_Rect &player_box, int player_status);

    bool getDead() const
    {
        return isDead;
    }

    SDL_Rect getBox() const
    {
        return mBox;
    }
private:
    int HP;
    SDL_Rect mBox, currentBox;
    SDL_Texture *mTexture, *bTexture, *eTexture;
    int mVelX, mVelY;
    int x_min, x_max;

    SDL_Rect Monster_Clips[FMONSTER_FRAME_NUM];
    int frame;

    bool on_ground;

    int map_x;
    int map_y;
    int thinkTime;
    vector <Bullet*> bullets;

    int status;
    Input input_type;
    bool isDead;
    bool BullHitting;
    Animation idle = Animation(0, 8, 96, 96, 16);
    Animation run = Animation(1, 7, 96, 96, 8);
    Animation attack = Animation(2, 10, 96, 96, 8);
    Animation hurt = Animation(3, 4, 96, 96, 12);
    Animation dead = Animation(4, 13, 96, 96, 8);
    vector <Animation> animations;
};

class FlyingMonsterFamily
{
public:
    FlyingMonsterFamily(SDL_Texture *p_texture = nullptr, SDL_Texture *b_texture = nullptr, SDL_Texture *e_tex = nullptr);
    void show(RenderWindow &window, SDL_Rect &mCamera, const Input &input, const SDL_Rect &player_box, int player_status, GameState &state);
    void move(const SDL_Rect &player_box, Tile* map_data);
    bool isAttack(const Input &input, const SDL_Rect &player_box, const SDL_Rect &player_currentBox, const int &player_status);
    void checkDied();
    bool isWin();

private:
    vector <FlyingMonster> FlyingMonsters;
    int cntDarkWarriorDied;
};

#endif // FLYINGMONSTER_H_INCLUDED
