#include "ThreatsObject.h"

ThreatsObject::ThreatsObject(){
    width_frame = 0;
    height_frame = 0;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    on_ground = false;
    frame = 0;
}

ThreatsObject::~ThreatsObject(){

}

bool ThreatsObject::loadIMG(string filePath, SDL_Renderer* ren){
    bool ret = renderWindow::loadIMG(filePath, ren);
    if(ret){
        width_frame = rect.w/THREAT_FRAME_NUM;
        height_frame = rect.h;
    }
    return ret;
}

void ThreatsObject::set_clips(){
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

void ThreatsObject::show(SDL_Renderer* des){
    rect.x = x_pos - map_x;
    rect.y = y_pos - map_y;
    frame++;
    if(frame >= 8){
        frame = 0;
    }

    SDL_Rect* current_clip = &frame_clip[frame];
    SDL_Rect render_quad = {rect.x, rect.y, width_frame, height_frame};

    SDL_RenderCopy(des, g_texture, current_clip, &render_quad);
}

void ThreatsObject::doPlayer(Map& gMap){
     x_val = 0;
        y_val += THREATS_GRAVITY_SPEED;
        if(y_val >= THREARS_MAX_FALL_SPEED)
        {
            y_val = THREARS_MAX_FALL_SPEED;
        }
        checkToMap(gMap);
}

void ThreatsObject::checkToMap(Map& gMap){
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
            if(gMap.tile[y1][x2] != BLANK_TILE || gMap.tile[y1][x2] != BLANK_TILE)
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
            else if(x_val < 0)
            {
                if(gMap.tile[y1][x1] != BLANK_TILE || gMap.tile[y2][x1] != BLANK_TILE)
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
            if(gMap.tile[y2][x1] != BLANK_TILE || gMap.tile[y2][x2] != BLANK_TILE)
            {
                y_pos = y2*TILE_SIZE;
                y_pos -= height_frame + 1;
                y_val = 0;
                on_ground = true;
            }
            else if(y_val < 0)
            {
                if(gMap.tile[y1][x1] != BLANK_TILE || gMap.tile[y1][x1] != BLANK_TILE)
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
    else if(x_pos + width_frame > gMap.max_x)
    {
        x_pos = gMap.max_x - width_frame - 1;
    }
}
