#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include "Header.h"
#include "renderWindow.h"

#define TOTAL_TILE 20

class TileMap: public renderWindow{
public:

};

class gameMap{
public:
    void LoadMap(string filePath);
    void LoadTile(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map;};
    void setMap(Map& map_data) {game_map = map_data;};

private:
    Map game_map;
    TileMap tile_map[TOTAL_TILE];
};

#endif // GAMEMAP_H_INCLUDED
