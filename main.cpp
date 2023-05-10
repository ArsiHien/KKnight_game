#include "Game.h"
#include "Timer.h"
#include <iostream>

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
    Game game;
    LTimer capTimer;
    if(!game.init())
    {
        cout << "Failed to init\n";
    }
    else
    {
        if(!game.loadMedia())
        {
            cout << "Failed to load media\n";
            game.close();
        }
        else
        {
            SDL_Event event;
            while(game.isRunning())
            {
                capTimer.start();
                switch (game.getState())
                {
                case STATE_START_MENU:
                    while(SDL_PollEvent(&event)) game.handleStartMenuEvent(event);
                    game.renderStartMenu();
                    break;
                case STATE_GUIDE:
                    while(SDL_PollEvent(&event)) game.handleGuideEvent(event);
                    game.renderGuide();
                    break;
                case STATE_PAUSE_MENU:
                case STATE_GAME_OVER_MENU:
                case STATE_WIN_MENU:
                    while(SDL_PollEvent(&event)) game.handleSubMenu(event);
                    game.renderSubMenu();
                    break;
                case STATE_PLAY:
                    while (SDL_PollEvent(&event)) game.handleGameEvent(event);
                    game.renderGame();
                    break;
                default:
                    break;
                }
                int frameTicks = capTimer.getTicks();
                if( frameTicks < SCREEN_TICKS_PER_FRAME )
                {
                    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
                }
            }
        }
    }
    game.close();
    return 0;
}
