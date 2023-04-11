#include "Enemy.h"

Monster::Monster()
{
    HP = 150;
    on_ground = false;
    frame = 0;
    mBox = {0, 0, 60, 60};
    x_pos = 0;
    y_pos = 0;
    mVelX = 0;
    mVelY = 0;
    map_x = 0;
    map_y = 0;
}

Monster::~Monster()
{

}

void Monster::loadMonsterTexture(RenderWindow &window)
{
    mTexture = window.loadIMG("gfx/threat_level.png");
    if(mTexture == nullptr)
    {
        cout << "Failed to load player texture\n";
    }
}

void Monster::set_clips()
{
    for(int i = 0; i < MONSTER_FRAME_NUM; i++)
    {
        frame_clip[i].x = i*MONSTER_WIDTH;
        frame_clip[i].y = 0;
        frame_clip[i].w = MONSTER_WIDTH;
        frame_clip[i].h = MONSTER_HEIGHT;
    }
}

void Monster::show(RenderWindow &window)
{
    mBox.x = x_pos - map_x;
    mBox.y = y_pos - map_y;
    frame++;
    if(frame >= 8)
    {
        frame = 0;
    }
    SDL_Rect* current_clip = &frame_clip[frame];
    window.render(mTexture, mBox.x, mBox.y, mBox.w, mBox.h, current_clip);
}

void Monster::doPlayer(Tile* map_data)
{
    mVelX = 0;
    mVelY += MONSTER_GRAVITY_SPEED;
    if(mVelY >= MONSTER_MAX_FALL_SPEED)
    {
        mVelY = MONSTER_MAX_FALL_SPEED;
    }
    checkToMap(map_data);
}

void Monster::checkToMap(Tile *map_data)
{
    x_pos += mVelX;
    if( ( x_pos < 0 ) || ( x_pos + MONSTER_WIDTH > LEVEL_WIDTH ) || touchesWall( map_data ) )
    {
        x_pos -= mVelX;
    }
    y_pos += mVelY;
    if( ( y_pos < 0 ) || ( y_pos + MONSTER_HEIGHT > LEVEL_HEIGHT ) || touchesWall( map_data)  )
    {
        y_pos -= mVelY;
    }
}

bool Monster::checkCollision(SDL_Rect b )
{
    int leftA = x_pos, leftB = b.x;
    int rightA = x_pos + MONSTER_WIDTH, rightB = b.x + b.w;
    int topA = y_pos, topB = b.y;
    int bottomA = y_pos + MONSTER_HEIGHT, bottomB = b.y + b.h;

    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
    {
        if(bottomA <= topB) on_ground = true;
        return false;
    }
    return true;
}

bool Monster::touchesWall(Tile *map_data)
{
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if(map_data[i].getType() != -1)
        {
            if( checkCollision(map_data[i].getBox()) )
            {
                return true;
            }
        }
    }
    return false;
}

void Monster::isAttacked(Input i, SDL_Rect box, SDL_Rect currentBox, int status)
{
    if(i.attack1 == 1 || i.attack2 == 1 || i.attack3 == 1)
    {
        if(status == RIGHT)
        {
            if(box.x < x_pos && checkCollision(currentBox))
            {
                HP--;
            }
        }
        if(status == LEFT)
        {
            if(box.x >= x_pos && checkCollision(currentBox))
            {
                HP--;
            }
        }
    }
}

bool Monster::isAttacking(Input i, SDL_Rect box, int status)
{
    if(i.defend == 0 )
    {
        if(checkCollision(box))
        {
            return true;
        }
    }
    return false;
}
