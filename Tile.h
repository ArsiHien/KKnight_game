#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "Header.h"
#include "RenderWindow.h"

class Tile
{
public:
    Tile(int x = 0, int y = 0, int tileType = 0);

    void render(SDL_Texture *mTexture, RenderWindow& window, SDL_Rect& camera, SDL_Rect &clip);
    int getType();
    SDL_Rect getBox();

private:
    SDL_Rect mBox;
    int mType;
};

#endif // TILE_H_INCLUDED
