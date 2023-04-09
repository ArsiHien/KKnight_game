#include "Header.h"
#include "RenderWindow.h"
#include "GameMap.h"
#include "Player.h"
#include "Enemy.h"

SDL_Event event;

RenderWindow windowScreen;
SDL_Rect fullScreen = {0, 0, SCREEN_HEIGHT, SCREEN_WIDTH};

vector <Monster*> makeThreatList()
{
    vector <Monster*> list_threats;
    Monster* threats_objs = new Monster[3];

    for(int i = 0; i < 3; i++)
    {
        Monster* p_threat = (threats_objs + i);
        if(p_threat != nullptr)
        {
            p_threat->loadMonsterTexture(windowScreen);
            p_threat->set_clips();
            p_threat->set_x_pos(200 + i*500);;
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

int main(int argc, char* argv[])
{
    windowScreen.initWindow();

    SDL_Texture *tex = windowScreen.loadIMG("gfx/background.png");


    bool gameRunning = true;
    GameMap Map;
    SDL_Rect mCamera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Map.setTiles();
    Map.loadTileTexture(windowScreen);

    Tile *map_data = Map.getMap();
    Player knight;
    knight.setClips();
    knight.loadPlayerTexture(windowScreen);

    vector <Monster*> threats_list = makeThreatList();

    while(gameRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) gameRunning = false;
            knight.handleEvent(event);
        }

        windowScreen.clearScreen();

        windowScreen.render(tex,0, 0, 1280, 640);

        Map.render(windowScreen, mCamera);

        knight.doPlayer(map_data);
        knight.centerPlayerOnMap(mCamera);
        knight.show(windowScreen, mCamera);
        knight.drawHP(*windowScreen.getRenderer(), mCamera);
        if(knight.isDead())
        {
            tex = windowScreen.loadIMG("gfx/Game_Over_logo.png");
            windowScreen.render(tex,0, 0, 1280, 640);
            windowScreen.display();
        }

        for(int i = 0; i < threats_list.size(); i++)
        {
            Monster* p_threat = threats_list.at(i);
            if(p_threat != nullptr)
            {
                p_threat->setMapXY(mCamera.x, mCamera.y);
                p_threat->doPlayer(map_data);
                p_threat->show(windowScreen);
                p_threat->isAttacked(knight.getInputType(), knight.getBox());
                if(p_threat->getHP() <= 0)
                {
                    threats_list.erase(threats_list.begin() + i);
                }
                knight.isHitted(p_threat->isAttacking(knight.getInputType(), knight.getBox()));
            }
        }
        if(threats_list.size() == 0){
            tex = windowScreen.loadIMG("gfx/win.png");
            windowScreen.render(tex,0, 0, 1280, 640);
        }
        windowScreen.display();
    }
    windowScreen.quitSDL();

    return 0;
}
