#include "Menu.h"

Menu::Menu(SDL_Texture *menu_texture, SDL_Texture *bg_texture)
{
    bgTexture = bg_texture;
    backgroundBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    for(int i = 0, x = 0, y = 0; i < TOTAL_BACKGROUND; i++, y+= BACKGROUND_TEXTURE_HEIGHT)
    {
        backgroundClip[i] = {x, y, BACKGROUND_TEXTURE_WIDTH, BACKGROUND_TEXTURE_HEIGHT};
    }
    mTexture = menu_texture;
    menuBackgroundBox = {SCREEN_WIDTH/2 - MENU_BACKGROUND_WIDTH/2, SCREEN_HEIGHT/2 - MENU_BACKGROUND_HEIGHT/2, MENU_BACKGROUND_WIDTH, MENU_BACKGROUND_HEIGHT};
    menuBackgroundClip = {0, 640, MENU_BACKGROUND_TEXTURE_WIDTH, MENU_BACKGROUND_TEXTURE_HEIGHT};
    titleBox = {SCREEN_WIDTH/2 - MENU_TITLE_WIDTH/2, menuBackgroundBox.y + 60, MENU_TITLE_WIDTH, MENU_TITLE_HEIGHT};
    for(int i = 0, y = 640, x = 960; i < TOTAL_TITLE; i++, y += 160)
    {
        titleClips[i] = {x, y, MENU_TITLE_TEXTURE_WIDTH, MENU_TITLE_TEXTURE_HEIGHT};
    }
    for(int i = 0, x = 800, y = 200; i < 3; i++, y += 100)
    {
        buttonBox[i] = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT};
    }
    buttonBox[CONTINUE] = {menuBackgroundBox.x + 80, menuBackgroundBox.y + menuBackgroundBox.h - 200, LONG_BUTTON_WIDTH, LONG_BUTTON_HEIGHT};
    buttonBox[PLAY_AGAIN] = {menuBackgroundBox.x + 80, menuBackgroundBox.y + menuBackgroundBox.h - 200, LONG_BUTTON_WIDTH, LONG_BUTTON_HEIGHT};
    buttonBox[QUIT2] = {menuBackgroundBox.x + menuBackgroundBox.w - 80 - BUTTON_WIDTH, buttonBox[CONTINUE].y, BUTTON_WIDTH, BUTTON_HEIGHT};
    buttonBox[HOME] = {SCREEN_WIDTH/2 - BUTTON_WIDTH/2, 500, BUTTON_WIDTH, BUTTON_HEIGHT};
    for(int i = 0, x = 0; i < 4; i++, x += BUTTON_TEXTURE_WIDTH)
    {
        for(int j = 0, y = 0; j < 2; j++, y += BUTTON_TEXTURE_HEIGHT)
        {
            buttonClips[i][j] = {x, y, BUTTON_TEXTURE_WIDTH, BUTTON_TEXTURE_HEIGHT};
        }
    }
    for(int i = 4, x = 0; i < 7; i++, x += LONG_BUTTON_TEXTURE_WIDTH)
    {
        for(int j = 0, y = 2*BUTTON_TEXTURE_HEIGHT; j < 2; j++, y += LONG_BUTTON_TEXTURE_HEIGHT)
        {
            buttonClips[i][j] = {x, y, LONG_BUTTON_TEXTURE_WIDTH, LONG_BUTTON_TEXTURE_HEIGHT};
        }
    }
    buttonClips[QUIT2][0] = buttonClips[QUIT1][0];
    buttonClips[QUIT2][1] = buttonClips[QUIT1][1];
    guideClip = {960, 1120, 1280, 640};
    for(int i = 0; i < TOTAL_BUTTON; i++) mouseover[i] = 0;
}

void Menu::handleEvent(SDL_Event &e, GameState &state, Mix_Chunk *gSound[])
{
    if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION)
        for(int i = 0; i < TOTAL_BUTTON; i++)
            mouseover[i] = 0;
    int x, y;
    SDL_GetMouseState(&x, &y);
    for(int i = 0; i < TOTAL_BUTTON; i++)
    {
        bool inside = false;
        if(state == STATE_START_MENU)
        {
            if(i == PLAY || i == GUIDE || i == QUIT1)
            {
                if(buttonBox[i].x <= x && x <= buttonBox[i].x + buttonBox[i].w && buttonBox[i].y <= y && y <= buttonBox[i].y + buttonBox[i].h)
                {
                    inside = true;
                }
            }
        }
        else if (state == STATE_PAUSE_MENU)
        {
            if(i == CONTINUE || i == QUIT2)
            {
                if(buttonBox[i].x <= x && x <= buttonBox[i].x + buttonBox[i].w && buttonBox[i].y <= y && y <= buttonBox[i].y + buttonBox[i].h)
                {
                    inside = true;
                }
            }
        }
        else if (state == STATE_WIN_MENU || state == STATE_GAME_OVER_MENU)
        {
            if(i == PLAY_AGAIN || i == QUIT2)
            {
                if(buttonBox[i].x <= x && x <= buttonBox[i].x + buttonBox[i].w && buttonBox[i].y <= y && y <= buttonBox[i].y + buttonBox[i].h)
                {
                    inside = true;
                }
            }
        }
        else if(state == STATE_GUIDE){
            if(i == HOME)
            {
                if(buttonBox[i].x <= x && x <= buttonBox[i].x + buttonBox[i].w && buttonBox[i].y <= y && y <= buttonBox[i].y + buttonBox[i].h)
                {
                    inside = true;
                }
            }
        }
        if(inside)
        {
            switch (e.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    Mix_PlayChannel(-1, gSound[SELECT_BUTTON_SOUND], 0);
                    if(i == PLAY || i == CONTINUE) state = STATE_PLAY;
                    else if(i == QUIT1 || i == QUIT2) state = STATE_QUIT;
                    else if(i == PLAY_AGAIN) state = STATE_AGAIN;
                    else if(i == GUIDE) state = STATE_GUIDE;
                    else if(i == HOME) state = STATE_START_MENU;
                }
                break;
            case SDL_MOUSEMOTION:
                mouseover[i] = 1;
                break;
            }
        }
    }
}

void Menu::renderBackgroundInGame(RenderWindow &window)
{
    window.renderB(bgTexture, &backgroundBox, &backgroundClip[BACKGROUND_INGAME]);
}

void Menu::renderMenuStart(RenderWindow &window)
{
    window.renderB(bgTexture, &backgroundBox, &backgroundClip[BACKGROUND_START]);
    for(int i = 0; i < 3; i++)
    {
        window.renderB(mTexture, &buttonBox[i], &buttonClips[i][mouseover[i]]);
    }
}

void Menu::renderMenuInGame(RenderWindow &window, GameState &state)
{
    window.renderB(mTexture, &menuBackgroundBox, &menuBackgroundClip);
    for(int i = 4; i < 7; i++)
    {
        switch (state)
        {
        case STATE_PAUSE_MENU:
            window.renderB(mTexture, &titleBox, &titleClips[PAUSE]);
            if(i == CONTINUE || i == QUIT2){
                window.renderB(mTexture, &buttonBox[i], &buttonClips[i][mouseover[i]]);
            }
            break;
        case STATE_GAME_OVER_MENU:
            window.renderB(mTexture, &titleBox, &titleClips[GAMEOVER]);
            if(i == PLAY_AGAIN || i == QUIT2){
                window.renderB(mTexture, &buttonBox[i], &buttonClips[i][mouseover[i]]);
            }
            break;
        case STATE_WIN_MENU:
            window.renderB(mTexture, &titleBox, &titleClips[VICTORY]);
            if(i == PLAY_AGAIN || i == QUIT2){
                window.renderB(mTexture, &buttonBox[i], &buttonClips[i][mouseover[i]]);
            }
            break;
        default:
            break;
        }
    }
}

void Menu::renderGuide(RenderWindow &window){
    window.renderB(mTexture, &backgroundBox, &guideClip);
    window.renderB(mTexture, &buttonBox[HOME], &buttonClips[HOME][mouseover[HOME]]);
}
