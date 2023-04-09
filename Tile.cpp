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

void Tile::render(SDL_Texture *mTexture, RenderWindow &window, SDL_Rect& camera, SDL_Rect &clip )
{
    window.render(mTexture, mBox.x - camera.x, mBox.y - camera.y, TILE_SIZE, TILE_SIZE, &clip );
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}
