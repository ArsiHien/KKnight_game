#ifndef DARKWARRIOR_H_INCLUDED
#define DARKWARRIOR_H_INCLUDED

#include "Enemy.h"

//const int MONSTER_FRAME_NUM = 39;
//
//const int MONSTER_SPEED = 1;
//const int MONSTER_GRAVITY_SPEED = 1;
//const int MONSTER_MAX_FALL_SPEED = 8;
//const int MAX_MONSTER_ATTACK = 3;
//const int MAX_MONSTER_DELAY = 120;

class DarkWarrior : protected Monster{
public:
    DarkWarrior();
    ~DarkWarrior();

    void show(RenderWindow &window);

private:
    SDL_Rect mBox;
    SDL_Rect currentBox;
};

#endif // DARKWARRIOR_H_INCLUDED
