#include "Hero.h"

Hero::Hero()
{
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status = WALK_NONE;
    input_type.left = 0;
    input_type.right = 0;
    input_type.down = 0;
    input_type.up = 0;
    on_ground = false;
    map_x = 0;
    map_y = 0;
    come_back_time = 0;
}

Hero::~Hero()
{

}

bool Hero::loadIMG(const string filePath, SDL_Renderer* ren)
{
    bool ret = renderWindow::loadIMG(filePath, ren);
    if(ret == true)
    {
        width_frame = rect.w/8;
        height_frame = rect.h;
    }
    return ret;
}

void Hero::setClips()
{
    if(width_frame > 0 && height_frame > 0)
    {
        for(int i = 0; i < 8; i++)
        {
            frame_clip[i].x = i*width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void Hero::show(SDL_Renderer* des)
{
    updateImagePlayer(des);
    if(input_type.left == 1 || input_type.right == 1)
    {
        frame = ++frame%8;
    }
    else
    {
        frame = 0;
    }

    if(come_back_time == 0)
    {
        rect.x = x_pos - map_x;
        rect.y = y_pos - map_y;

        SDL_Rect* current_clip = &frame_clip[frame];
        SDL_Rect render_quad = {rect.x, rect.y, width_frame, height_frame};

        SDL_RenderCopy(des, g_texture, current_clip, &render_quad);
    }
}

void Hero::handelInputAction(SDL_Event event, SDL_Renderer* ren)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_d:
            status = WALK_RIGHT;
            input_type.right = 1;
            input_type.left = 0;
            updateImagePlayer(ren);
            break;
        case SDLK_a:
            status = WALK_LEFT;
            input_type.left = 1;
            input_type.right = 0;
            updateImagePlayer(ren);
            break;
        case SDLK_w:
            input_type.jump = 1;
            break;
        }
    }
    else if(event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_d:
            input_type.right = 0;
            break;
        case SDLK_a:
            input_type.left = 0;
            break;
        }
    }
    if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            danBan* p_dan = new danBan();
            p_dan -> loadIMG("gfx/dan.png", ren);
            p_dan -> setRect(this -> rect.x + width_frame - 20, rect.y + height_frame*0.3);
            p_dan ->set_x_val(20);
            p_dan ->set_is_move(true);

            p_luong_dan.push_back(p_dan);
        }
    }
}

void Hero::handleDan(SDL_Renderer* des){
    for(int i = 0; i < p_luong_dan.size(); i++){
        danBan* p_dan = p_luong_dan.at(i);
        if(p_dan != nullptr){
            if(p_dan->get_is_move() == true){
                p_dan->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_dan->renderTexture(des);
            }
            else{
                p_luong_dan.erase(p_luong_dan.begin() + i);
                if(p_dan != nullptr){
                    delete p_dan;
                    p_dan = nullptr;
                }
            }
        }
    }
}

void Hero::doPlayer(Map& map_data)
{
    if(come_back_time == 0)
    {
        x_val = 0;
        y_val += GRAVITY_SPEED;
        if(y_val >= MAX_FALL_SPEED)
        {
            y_val = MAX_FALL_SPEED;
        }
        if(input_type.left == 1)
        {
            x_val -= PLAYER_SPEED;
        }
        else if(input_type.right == 1)
        {
            x_val += PLAYER_SPEED;
        }
        if(input_type.jump == 1)
        {
            if(on_ground == true)
            {
                y_val -= PLAYR_JUMP_VAL;
                on_ground = false;
            }
            input_type.jump = 0;
        }
        checkToMap(map_data);
        centerEntityOnMap(map_data);
    }

    else
    {
        come_back_time--;
        if(come_back_time == 0)
        {
            on_ground = false;
            if(x_pos > 256)
            {
                x_pos -= 256;
            }
            else x_pos = 0;
            y_pos = 0;
            x_val = 0;
            y_val = 0;
        }
    }
}

void Hero::checkToMap(Map& map_data)
{
    int x1 = 0, x2 = 0;
    int y1 = 0, y2 = 0;

    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 1)/TILE_SIZE;

    y1 = y_pos/TILE_SIZE;
    y2 = (y_pos + height_frame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >=0 && MAX_MAP_Y)
    {
        if(x_val > 0)
        {
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
            else if(x_val < 0)
            {
                if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
                {
                    x_pos = (x1 + 1)*TILE_SIZE;
                    x_val = 0;
                }
            }
        }
    }

    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = x_pos/TILE_SIZE;
    x2 = (x_pos + width_min)/TILE_SIZE;

    y1 = (y_pos + y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + height_frame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >=0 && MAX_MAP_Y)
    {
        if(y_val > 0)
        {
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                y_pos = y2*TILE_SIZE;
                y_pos -= height_frame + 1;
                y_val = 0;
                on_ground = true;
                if(status == WALK_NONE){
                    status = WALK_RIGHT;
                }
            }
            else if(y_val < 0)
            {
                if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x1] != BLANK_TILE)
                {
                    y_pos = (y1 + 1)*TILE_SIZE;
                    y_val = 0;
                }
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;
    if(x_pos < 0)
    {
        x_pos = 0;
    }
    else if(x_pos + width_frame > map_data.max_x)
    {
        x_pos = map_data.max_x - width_frame - 1;
    }
    if(y_pos > map_data.max_y)
    {
        come_back_time = 60;
    }
}

void Hero::centerEntityOnMap(Map& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH)/2;
    if(map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if(map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }

    map_data.start_y = y_pos - (SCREEN_HEIGHT)/2;
    if(map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if(map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
    {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}

void Hero::updateImagePlayer(SDL_Renderer* des)
{
    if(on_ground == true)
    {
        if(status == WALK_LEFT)
        {
            loadIMG("gfx/player_left.png", des);
        }
        else
        {
            loadIMG("gfx/player_right.png", des);
        }
    }
    else
    {
        if(status == WALK_LEFT)
        {
            loadIMG("gfx/jum_left.png", des);
        }
        else
        {
            loadIMG("gfx/jum_right.png", des);
        }
    }
}
