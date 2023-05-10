#include "Game.h"

bool Game::init()
{
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    running = true;

    if(!window.initWindow()) return false;
    state = STATE_START_MENU;
    return true;
}

void Game::setMap()
{
    SDL_Rect mCamera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Map = GameMap(gTexture[MAP_TEXTURE]);
    Map.setTiles();
    map_data = Map.getMap();
}

void Game::setPlayer()
{
    knight = Player(gTexture[PLAYER_TEXTURE], gTexture[POTION_TEXTURE]);
}

void Game::setDarkWarrior()
{
    darkWarriors = DarkWarriorFamily(gTexture[DARK_WARRIOR_TEXTURE]);
}

void Game::setFlyingMonster()
{
    flyingMonsters = FlyingMonsterFamily(gTexture[FLYING_MONSTER_TEXTURE], gTexture[BULLET_TEXTURE], gTexture[EXPLOSION_TEXTURE]);
}

void Game::setBoss()
{
    boss = Boss(6400, 480, gTexture[BOSS_TEXTURE]);
}

void Game::setMenu()
{
    menu = Menu(gTexture[MENU_TEXTURE], gTexture[BACKGROUND_TEXTURE]);
}

void Game::setDynamicObject()
{
    setPlayer();
    setDarkWarrior();
    setFlyingMonster();
    setBoss();
    hp = 0;
}


bool Game::loadImage()
{
    bool success = true;
    gTexture[BACKGROUND_TEXTURE] = window.loadIMG("gfx/background.png");
    if(gTexture[BACKGROUND_TEXTURE] == nullptr)
    {
        cout << "Failed to load background texture\n";
        success = false;
    }
    gTexture[MENU_TEXTURE] = window.loadIMG("gfx/menu.png");
    if(gTexture[MENU_TEXTURE] == nullptr)
    {
        cout << "Failed to load menu texture\n";
        success = false;
    }
    gTexture[MAP_TEXTURE] = window.loadIMG("map/mainlev_build.png");
    if(gTexture[MAP_TEXTURE] == nullptr)
    {
        cout << "Failed to load map texture\n";
        success = false;
    }
    gTexture[PLAYER_TEXTURE] = window.loadIMG("gfx/Knight.png");
    if(gTexture[PLAYER_TEXTURE] == nullptr)
    {
        cout << "Failed to load player texture\n";
        success = false;
    }
    gTexture[DARK_WARRIOR_TEXTURE] = window.loadIMG("gfx/darkwarrior.png");
    if(gTexture[DARK_WARRIOR_TEXTURE] == nullptr)
    {
        cout << "Failed to load darkWarrior texture\n";
        success = false;
    }
    gTexture[FLYING_MONSTER_TEXTURE] = window.loadIMG("gfx/flyingmonster.png");
    if(gTexture[FLYING_MONSTER_TEXTURE] == nullptr)
    {
        cout << "Failed to load flyingMonster texture\n";
        success = false;
    }
    gTexture[BULLET_TEXTURE] = window.loadIMG("gfx/Bullet.png");
    if(gTexture[BULLET_TEXTURE] == nullptr)
    {
        cout << "Failed to load bullet texture\n";
        success = false;
    }
    gTexture[EXPLOSION_TEXTURE] = window.loadIMG("gfx/explosion.png");
    if(gTexture[EXPLOSION_TEXTURE] == nullptr)
    {
        cout << "Failed to load explosion texture\n";
        success = false;
    }
    gTexture[BOSS_TEXTURE] = window.loadIMG("gfx/boss.png");
    if(gTexture[BOSS_TEXTURE] == nullptr)
    {
        cout << "Failed to load boss texture\n";
        success = false;
    }
    gTexture[POTION_TEXTURE] = window.loadIMG("gfx/HP.png");
    if(gTexture[POTION_TEXTURE] == nullptr)
    {
        cout << "Failed to load potion texture\n";
        success = false;
    }
    setMenu();
    setMap();
    return success;
}

bool Game::loadMusic()
{
    bool success = true;

    menuSound[SELECT_BUTTON_SOUND] = Mix_LoadWAV("sounds/select-button.wav");
    if (menuSound[SELECT_BUTTON_SOUND] == nullptr)
    {
        printf("Failed to load select button sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    menuTheme = Mix_LoadMUS("sounds/menu.mp3");
    if (menuTheme == nullptr)
    {
        printf("Failed to load menu theme music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    gameTheme = Mix_LoadMUS("sounds/inGame.mp3");
    if (gameTheme == nullptr)
    {
        printf("Failed to load game theme music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}

bool Game::loadFont()
{
    bool success = true;
    font[FONT_16] = TTF_OpenFont("fonts/Pixel-UniCode.ttf", 40);
    if (font[FONT_16] == nullptr)
    {
        printf("Failed to load font 16, error: %s\n", TTF_GetError());
        success = false;
    }
    font[FONT_32] = TTF_OpenFont("fonts/Pixel-UniCode.ttf", 32);
    if (font[FONT_32] == nullptr)
    {
        printf("Failed to load font 32, error: %s\n", TTF_GetError());
        success = false;
    }
    return success;
}

bool Game::loadMedia()
{
    bool success = true;
    if(!loadImage())
    {
        cout << "Failed to load image\n";
        success = false;
    }
    if(!loadMusic())
    {
        cout << "Failed to load music\n";
        success = false;
    }
    if(!loadFont())
    {
        cout << "Failed to load font\n";
        success = false;
    }
    return success;
}

bool Game::isRunning()
{
    return running;
}

int Game::getState()
{
    return state;
}

void Game::handleStartMenuEvent(SDL_Event &event)
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(menuTheme, -1);
        Mix_VolumeMusic(46);
    }
    if(event.type == SDL_QUIT)
    {
        running = false;
    }
    menu.handleEvent(event, state, menuSound);
    if(state == STATE_PLAY)
    {
        setDynamicObject();
        Mix_HaltMusic();
    }
    else if(state == STATE_QUIT)
    {
        running = false;
    }
}

void Game::renderStartMenu()
{
    window.clearScreen();
    menu.renderMenuStart(window);
    window.display();
}

void Game::handleSubMenu(SDL_Event &event)
{
    if(event.type == SDL_QUIT)
    {
        running = false;
    }
    menu.handleEvent(event, state, menuSound);
    if(state == STATE_AGAIN)
    {
        state = STATE_PLAY;
        setDynamicObject();
    }
    else if(state == STATE_QUIT)
    {
        running = false;
    }
}

void Game::renderSubMenu()
{
    window.clearScreen();
    menu.renderBackgroundInGame(window);
    Map.render(window, camera);
    knight.show(window, camera);
    flyingMonsters.show(window, camera, knight.getInputType(), knight.getBox(), knight.getStatus(), state);
    darkWarriors.show(window, camera);
    menu.renderMenuInGame(window, state);
    renderHP();
    window.display();
}

void Game::handleGameEvent(SDL_Event &event)
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(gameTheme, -1);
        Mix_VolumeMusic(64);
    }
    if(event.type == SDL_QUIT)
    {
        running = false;
    }
    knight.handleEvent(event, state, hp);
}

void Game::renderGuide()
{
    window.clearScreen();
    menu.renderGuide(window);
    window.display();
}

void Game::handleGuideEvent(SDL_Event &event)
{
    if(event.type == SDL_QUIT)
    {
        running = false;
    }
    menu.handleEvent(event, state, menuSound);
}

void Game::renderHP()
{
    hpText.str("");
    hpText << "x " << hp;
    window.renderText(hpText.str().c_str(), font[FONT_16], 100, 45);
}

void Game::renderGame()
{
    window.clearScreen();
    menu.renderBackgroundInGame(window);
    map_data = Map.getMap();
    Map.render(window, camera);
    renderHP();

    if(knight.isDead()) state = STATE_GAME_OVER_MENU;

    knight.doPlayer(map_data);
    knight.centerPlayerOnMap(camera);
    knight.show(window, camera);
    knight.drawHP(*window.getRenderer(), camera);
    knight.isHittingPotion(hp);

    darkWarriors.move(knight.getBox(), map_data);
    darkWarriors.show(window, camera);
    darkWarriors.checkDied();

    flyingMonsters.move(knight.getBox(), map_data);
    flyingMonsters.show(window, camera, knight.getInputType(), knight.getBox(), knight.getStatus(), state);
    flyingMonsters.checkDied();

    knight.isHitted(darkWarriors.isAttack(knight.getInputType(), knight.getBox(), knight.getCurrentBox(), knight.getStatus()), 0);
    knight.isHitted(flyingMonsters.isAttack(knight.getInputType(), knight.getBox(), knight.getCurrentBox(), knight.getStatus()),0);

    if(flyingMonsters.isWin() && darkWarriors.isWin())
    {
        boss.setMapXY(camera.x, camera.y);
        boss.move(knight.getBox(), map_data);
        boss.show(window, knight.getBox());
        boss.drawHP(*window.getRenderer(), camera);
        boss.isAttacked(knight.getInputType(), knight.getBox(), knight.getCurrentBox(), knight.getStatus());
        boss.showSkillBoss(window, knight.getBox(), camera);
        knight.isHitted(boss.isAttacking(knight.getInputType(), knight.getBox()), 0);
        knight.isHitted(boss.isAttacking2(knight.getInputType(), knight.getBox()), 0);
        if(boss.getDead()) state = STATE_WIN_MENU;
    }

    window.display();
}

void Game::close()
{
    window.quitSDL();
    for (SDL_Texture *mTexture : gTexture)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }

    for (Mix_Chunk *mSound : menuSound)
    {
        Mix_FreeChunk(mSound);
        mSound = nullptr;
    }

    for(TTF_Font *mFont : font)
    {
        TTF_CloseFont(mFont);
        mFont = nullptr;
    }
    Mix_FreeMusic(menuTheme);
    menuTheme = nullptr;
    Mix_FreeMusic(gameTheme);
    gameTheme = nullptr;
}
