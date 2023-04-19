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

void freeTexture(SDL_Texture *Texture)
{
    if(Texture != nullptr)
    {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }
}

int main(int argc, char* argv[])
{
    windowScreen.initWindow();

    SDL_Texture *mTexture = windowScreen.loadIMG("gfx/background.png");
    SDL_Texture *play_again_button = windowScreen.loadIMG("gfx/play_again.png");
    SDL_Texture *exit_button = windowScreen.loadIMG("gfx/exit.png");

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
        windowScreen.render(mTexture,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        if(knight.isDead())
        {
            freeTexture(mTexture);
            threats_list.clear();
            mTexture = windowScreen.loadIMG("gfx/Game_Over_logo.png");
            windowScreen.render(mTexture,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            windowScreen.render(play_again_button, 1000, 150, 200, 200);
            windowScreen.render(exit_button, 100, 150, 200, 200);
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT) gameRunning = false;
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x = event.button.x;
                    int y = event.button.y;
                    if(pow((x - 100 - 100),2) + pow((y - 150 - 100),2) <= 10000) gameRunning = false;
                    else if(pow((x - 1000 - 100),2) + pow((y - 150 - 100),2) <= 10000)
                    {
                        freeTexture(mTexture);
                        mTexture = windowScreen.loadIMG("gfx/background.png");
                        knight = Player();
                        knight.setClips();
                        knight.loadPlayerTexture(windowScreen);
                        threats_list = makeThreatList();
                    }
                }

            }
        }
        else if(threats_list.size() == 0)
        {
            freeTexture(mTexture);
            mTexture = windowScreen.loadIMG("gfx/win.png");
            windowScreen.render(mTexture,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        else
        {
            Map.render(windowScreen, mCamera);

            knight.doPlayer(map_data);
            knight.centerPlayerOnMap(mCamera);
            knight.show(windowScreen, mCamera);
            knight.drawHP(*windowScreen.getRenderer(), mCamera);

            for(int i = 0; i < threats_list.size(); i++)
            {
                Monster* p_threat = threats_list.at(i);
                if(p_threat != nullptr)
                {
                    p_threat->setMapXY(mCamera.x, mCamera.y);
                    p_threat->move(knight.getBox(), map_data);
                    p_threat->show(windowScreen);
                    p_threat->isAttacked(knight.getInputType(), knight.getBox(), knight.getCurrentBox(), knight.getStatus());
                    p_threat->drawHP(*windowScreen.getRenderer(), mCamera);
                    if(p_threat->getDead())
                    {
                        threats_list.erase(threats_list.begin() + i);
                    }
                    knight.isHitted(p_threat->isAttacking(knight.getInputType(), knight.getBox()), p_threat->getStatus());
                }
            }
        }
        windowScreen.display();
    }
    freeTexture(mTexture);
    freeTexture(play_again_button);
    freeTexture(exit_button);
    windowScreen.quitSDL();
    return 0;
}
