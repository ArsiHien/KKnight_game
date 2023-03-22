#include "Header.h"
#include "renderWindow.h"
#include "gameMap.h"
#include "Hero.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

renderWindow background;
renderWindow windowSceen;

vector <ThreatsObject*> makeThreatList(){
    vector <ThreatsObject*> list_threats;
    ThreatsObject* threats_objs = new ThreatsObject[20];

    for(int i = 0; i < 20; i++){
        ThreatsObject* p_threat = (threats_objs + i);
        if(p_threat != nullptr){
            p_threat->loadIMG("gfx/threat_level.png", renderer);
            p_threat->set_clips();
            p_threat->set_x_pos(700 + i*1200);
            p_threat->set_y_pos(250);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

    windowSceen.initWindow(window, renderer);
    renderer = windowSceen.getRenderer();
    background.loadIMG("gfx/background.png", renderer);

    gameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTile(renderer);

    Hero player;
    player.loadIMG("gfx/player_right.png", renderer);
    player.setClips();

    vector <ThreatsObject*> threats_list = makeThreatList();
    cout << threats_list.size();

    bool gameRunning = true;

    while(gameRunning)
    {
        fps_timer.start();
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) gameRunning = false;
            player.handelInputAction(event, renderer);
        }

        windowSceen.clearScreen();
        background.renderTexture(renderer);

        Map map_data = game_map.getMap();

        player.handleDan(renderer);
        player.setMapXY(map_data.start_x, map_data.start_y);
        player.doPlayer(map_data);
        player.show(renderer);

        game_map.setMap(map_data);
        game_map.DrawMap(renderer);

        for(int i = 0; i < threats_list.size(); i++){
            ThreatsObject* p_threat = threats_list.at(i);
            if(p_threat != nullptr){
                p_threat->setMapXY(map_data.start_x, map_data.start_y);
                p_threat->doPlayer(map_data);
                p_threat->show(renderer);
            }
        }

        windowSceen.display();
        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;

        if(real_imp_time < time_one_frame){
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time > 0) SDL_Delay(delay_time);
        }
    }
    windowSceen.quitSDL();
    background.quitSDL();

    return 0;
}
