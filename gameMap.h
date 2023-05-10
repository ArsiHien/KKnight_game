#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include "Header.h"
#include "RenderWindow.h"
#include "Tile.h"

class GameMap
{
public:
    GameMap(SDL_Texture *p_texture = nullptr);
    void setTiles();
    void render(RenderWindow &window, SDL_Rect& camera);
    Tile* getMap() {return tileSet;}

private:
    Tile tileSet[TOTAL_TILES];
    SDL_Rect m_tileClips[TOTAL_TILE_SPRITES];
    SDL_Texture *mTexture;
};

#endif // GAMEMAP_H_INCLUDED
