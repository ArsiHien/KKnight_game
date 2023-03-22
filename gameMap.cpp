#include "Header.h"
#include "gameMap.h"

void gameMap::LoadMap(string filePath){
    ifstream mapFile (filePath);
    if(!mapFile.is_open()){
        cout << "Error! Cannot open mapFile" << endl;
        return;
    }

    game_map.max_x = 0;
    game_map.max_y = 0;

    for(int i = 0; i < MAX_MAP_Y; i++){
        for(int j = 0; j < MAX_MAP_X; j++){
            mapFile >> game_map.tile[i][j];
            int val = game_map.tile[i][j];
            if(val > 0){
                if(j > game_map.max_x) game_map.max_x = j;
                if(i > game_map.max_y) game_map.max_y = i;
            }
        }
    }
    game_map.max_x = (game_map.max_x + 1)*TILE_SIZE;
    game_map.max_y = (game_map.max_y + 1)*TILE_SIZE;

    game_map.start_x = 0;
    game_map.start_y = 0;
    game_map.file_name = filePath;

    mapFile.close();

    return;
}

void gameMap::LoadTile(SDL_Renderer* screen){
    string file_img;
    for(int i = 0; i < TOTAL_TILE; i++){
        file_img = "map/" + to_string(i) + ".png";
        ifstream mapImg (file_img);
        if(!mapImg.is_open()){
            continue;
        }
        mapImg.close();
        tile_map[i].loadIMG(file_img, screen);
    }
}

void gameMap::DrawMap(SDL_Renderer* screen){
    int x1, x2, y1, y2;

    int map_x, map_y;

    map_x = game_map.start_x/TILE_SIZE;
    x1 = (game_map.start_x%TILE_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = game_map.start_y/TILE_SIZE;
    y1 = (game_map.start_y%TILE_SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
    for(int i = y1; i < y2; i += TILE_SIZE){
        map_x = game_map.start_x/TILE_SIZE;
        for(int j = x1; j < x2; j += TILE_SIZE){
            int val = game_map.tile[map_y][map_x];
            if(val > 0){
                tile_map[val].setRect(j, i);
                tile_map[val].renderTexture(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
