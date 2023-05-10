#include "Header.h"
#include "GameMap.h"

GameMap::GameMap(SDL_Texture *p_texture)
{
    mTexture = p_texture;
}

void GameMap::setTiles()
{
    int x = 0;
    int y = 0;
    ifstream mapFile("map/map.txt");
    if(!mapFile.is_open())
    {
        cout << "Error! Cannot open mapFile" << endl;
        return;
    }
    int tileType = -1;
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        mapFile >> tileType;
        tileSet[i] = Tile(x, y, tileType);
        x += TILE_SIZE;
        if(x >= LEVEL_WIDTH)
        {
            x = 0;
            y += TILE_SIZE;
        }
    }
    x = 0;
    y = 0;
    for(int i = 0; i < TOTAL_TILE_SPRITES; i++)
    {
        m_tileClips[i].x = x;
        m_tileClips[i].y = y;
        m_tileClips[i].h = TILE_SIZE;
        m_tileClips[i].w = TILE_SIZE;

        x += TILE_SIZE;
        if(x >= TILE_FILE_SIZE)
        {
            x = 0;
            y += TILE_SIZE;
        }
    }
    mapFile.close();
}

void GameMap::render(RenderWindow &window, SDL_Rect &camera)
{
    for(int i = 0; i < TOTAL_TILES; i++)
        if(tileSet[i].getType() != -1)
            tileSet[i].render(mTexture, window, camera, m_tileClips[tileSet[i].getType()]);
}
