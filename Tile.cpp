#include "Tile.h"
#include "Player.h"

Tile::Tile(int x, int y, int tileType)
{
    mBox.x = x;
    mBox.y = y;
    mBox.w = TILE_SIZE;
    mBox.h = TILE_SIZE;

    mType = tileType;
}

bool checkCollision( SDL_Rect a, SDL_Rect b)
{
    int leftA = a.x, leftB = b.x;
    int rightA = a.x + a.w, rightB = b.x + b.w;
    int topA = a.y, topB = b.y;
    int bottomA = a.y + a.h, bottomB = b.y + b.h;

    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
    {
        return false;
    }
    return true;
}

void Tile::render(SDL_Texture *mTexture, RenderWindow &window, SDL_Rect& camera, SDL_Rect &clip )
{
    if(checkCollision(mBox, camera)){
        window.render(mTexture, mBox.x - camera.x, mBox.y - camera.y, TILE_SIZE, TILE_SIZE, &clip );
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}
