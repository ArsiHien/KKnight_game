#include "DarkWarrior.h"

DarkWarrior::DarkWarrior(int xp, int yp, SDL_Texture *p_texture)
{
    mTexture = p_texture;
    HP = 150;
    on_ground = false;
    frame = 0;
    hitting = false;
    status = LEFT;
    mBox = {xp, yp, 96, 96};
    x_min = xp - 150;
    x_max = xp + 150;
    mVelX = 0;
    mVelY = 0;
    map_x = 0;
    map_y = 0;
    isDead = false;
    thinkTime = SCREEN_FPS*1;
    animations.push_back(idle);
    animations.push_back(run);
    animations.push_back(attack);
    animations.push_back(hurt);
    animations.push_back(dead);
    set_clips();
}

DarkWarrior::~DarkWarrior()
{

}

void DarkWarrior::set_clips()
{
    int n = 0;
    for(int i = 0, y = 0; i < (int)animations.size(); i++)
    {
        if(i > 0) y += animations[i - 1].frame_height;
        for(int j = 0; j < animations[i].amount_of_frame; j++)
        {
            mClips[n].x = j*animations[i].frame_width;
            mClips[n].y = y;
            mClips[n].h = animations[i].frame_height;
            mClips[n].w = animations[i].frame_width;
            n++;
        }
    }
}

void DarkWarrior::show(RenderWindow &window)
{
    int dxr = 0, dxl = 0, dy = 0, slow = 1, t = 0;
    currentBox.x = mBox.x - map_x;
    currentBox.y = mBox.y - map_y;
    if(HP <= 0)
    {
        dxr = dead.denta_x_right, dxl = dead.denta_x_left, dy = dead.denta_y;
        slow = dead.slow_down;
        currentBox.w = dead.frame_width;
        currentBox.h = dead.frame_height;
        for(int i = 0; i <dead.index; i++)
        {
            t += animations[i].amount_of_frame;
        }
        frame++;
        if(frame >= dead.amount_of_frame*slow)
        {
            isDead = true;
        }
    }
    else if(input_type.hurt == 1)
    {
        dxr = hurt.denta_x_right, dxl = hurt.denta_x_left, dy = hurt.denta_y;
        slow = hurt.slow_down;
        currentBox.w = hurt.frame_width;
        currentBox.h = hurt.frame_height;
        for(int i = 0; i <hurt.index; i++)
        {
            t += animations[i].amount_of_frame;
        }
        frame++;
        if(frame >= hurt.amount_of_frame*slow)
        {
            frame = 0;
            input_type.hurt = 0;
        }
    }
    else if(input_type.attack == 1)
    {
        dxr = attack.denta_x_right, dxl = attack.denta_x_left, dy = attack.denta_y;
        slow = attack.slow_down;
        currentBox.w = attack.frame_width;
        currentBox.h = attack.frame_height;
        for(int i = 0; i <attack.index; i++)
        {
            t += animations[i].amount_of_frame;
        }
        frame++;
        if(frame == 10*attack.slow_down) hitting = true;
        else hitting = false;
        if(frame >= attack.amount_of_frame*slow)
        {
            frame = 0;
            input_type.attack = 0;
        }
    }
    else if(input_type.run == 1)
    {
        dxr = run.denta_x_right, dxl = run.denta_x_left, dy = run.denta_y;
        slow = run.slow_down;
        currentBox.w = run.frame_width;
        currentBox.h = run.frame_height;
        for(int i = 0; i <run.index; i++)
        {
            t += animations[i].amount_of_frame;
        }
        frame = ++frame%(run.amount_of_frame*slow);
    }
    else
    {
        dxr = idle.denta_x_right, dxl = idle.denta_x_left, dy = idle.denta_y;
        slow = idle.slow_down;
        currentBox.w = idle.frame_width;
        currentBox.h = idle.frame_height;
        for(int i = 0; i <idle.index; i++)
        {
            t += animations[i].amount_of_frame;
        }
        frame++;
        if(frame >= idle.amount_of_frame*slow)
        {
            frame = 0;
        }
    }
    SDL_Rect* current_clip = &mClips[t + frame/slow];
    if(status == RIGHT)
    {
        window.render(mTexture, currentBox.x - dxr, currentBox.y - dy, currentBox.w, currentBox.h, current_clip);
    }
    else
    {
        window.render(mTexture, currentBox.x - dxl, currentBox.y - dy, currentBox.w, currentBox.h, current_clip, 0.0, NULL, SDL_FLIP_HORIZONTAL);
    }
}

void DarkWarrior::move(const SDL_Rect &player_box, Tile* map_data)
{
    mVelX = 0;
    mVelY += DARK_WARRIOR_GRAVITY_SPEED;
    if(mVelY >= DARK_WARRIOR_MAX_FALL_SPEED)
    {
        mVelY = DARK_WARRIOR_MAX_FALL_SPEED;
    }
    if(thinkTime == 0 && HP > 0)
    {
        input_type.run = 1;
        input_type.right = 0;
        input_type.left = 0;
        int distance = sqrt(min(pow((x_min - player_box.x + player_box.w/2),2), pow((x_max - player_box.x + player_box.w/2),2)) + pow((mBox.y + mBox.h/2 - player_box.y + player_box.h/2), 2));
        if(mBox.x >= x_min && mBox.x <= x_max && distance <= 256)
        {
            if(player_box.x + player_box.w/2 == mBox.x + mBox.w/2) return;
            if(mBox.x == x_min || mBox.x == x_max) input_type.run = 0;
            if(player_box.x + player_box.w/2 < mBox.x + mBox.w/2)
            {
                status = LEFT;
                input_type.left = 1;
                input_type.right = 0;
            }
            else if(player_box.x + player_box.w/2 > mBox.x + mBox.w/2)
            {
                status = RIGHT;
                input_type.left = 0;
                input_type.right = 1;
            }
        }
        else if(distance > 256) input_type.run = 0;
        if(input_type.attack == 1) mVelX = 0;
        else if(input_type.left == 1)
        {
            mVelX = -DARK_WARRIOR_SPEED;
        }
        else if(input_type.right == 1) mVelX = DARK_WARRIOR_SPEED;
    }
    else input_type.run = 0;
    checkToMap(map_data);
}

void DarkWarrior::checkToMap(Tile *map_data)
{
    mBox.x += mVelX;
    if( ( mBox.x < 0 ) || (mBox.x < x_min) || (mBox.x > x_max) || ( mBox.x + mBox.w > LEVEL_WIDTH ) || touchesWall( map_data ) )
    {
        mBox.x -= mVelX;
    }
    mBox.y += mVelY;
    mBox.y = mBox.y;
    if( ( mBox.y < 0 ) || ( mBox.y + mBox.h > LEVEL_HEIGHT ) || touchesWall( map_data)  )
    {
        mBox.y -= mVelY;
    }
}

bool DarkWarrior::checkCollision( SDL_Rect a, SDL_Rect b)
{
    int leftA = a.x, leftB = b.x;
    int rightA = a.x + a.w, rightB = b.x + b.w;
    int topA = a.y, topB = b.y;
    int bottomA = a.y + a.h, bottomB = b.y + b.h;

    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool DarkWarrior::touchesWall(Tile *map_data)
{
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if(map_data[i].getType() != -1)
        {
            if( checkCollision(mBox, map_data[i].getBox()) )
            {
                return true;
            }
        }
    }
    return false;
}

void DarkWarrior::isAttacked(const Input &input, const SDL_Rect &player_box, const SDL_Rect &player_currentBox, const int &player_status)
{
    if(input.attack1 == 1 || input.attack2 == 1 || input.attack3 == 1)
    {
        if(player_status == RIGHT)
        {
            if(player_box.x + player_box.w/2 < mBox.x + mBox.w/2 + 15 && checkCollision(mBox, player_currentBox))
            {
                input_type.hurt = 1;
                HP--;
            }
        }
        if(player_status == LEFT)
        {
            if(player_box.x + player_box.w/2 >= mBox.x + mBox.w/2 - 20 && checkCollision(mBox, player_currentBox))
            {
                input_type.hurt = 1;
                HP--;
            }
        }
    }
}

bool DarkWarrior::isAttacking(const Input &input, SDL_Rect player_box)
{
    if(HP <= 0 || input_type.hurt == 1) return false;
    SDL_Rect Attack_box = {mBox.x + mBox.w/2 - attack.frame_width/2, mBox.y + mBox.h - attack.frame_height, attack.frame_width, attack.frame_height};
    if(thinkTime > 0)
    {
        thinkTime--;
        if(!checkCollision(Attack_box, player_box)) return false;
        return hitting;
    }
    if(checkCollision(Attack_box, player_box))
    {
        if(input.dead != 1)
        {
            input_type.attack = 1;
            frame = 0;
            thinkTime = SCREEN_FPS*1;
        }
        if(input.defend == 0)
        {
            if(status == RIGHT)
            {
                if(player_box.x + 16 >= mBox.x + 32)
                {
                    return hitting;
                }
            }
            if(status == LEFT)
            {
                if(player_box.x + 16 <= mBox.x + 160)
                {
                    return hitting;
                }
            }
        }
    }
    return false;
}

void DarkWarrior::drawHP(SDL_Renderer &ren, SDL_Rect &mCamera)
{
    if(HP <= 0) return;
    SDL_Rect health_box = {mBox.x + mBox.w/2 - HP/10 - mCamera.x, mBox.y - 5 - mCamera.y, HP/5, 5};

    SDL_SetRenderDrawColor(&ren, 255, 0, 0, 255);
    SDL_RenderFillRect(&ren, &health_box);

    SDL_SetRenderDrawColor(&ren, 0, 0, 255, 255);
    SDL_RenderDrawRect(&ren, &health_box);
}

DarkWarriorFamily::DarkWarriorFamily(SDL_Texture *p_texture)
{
    darkWarriors.push_back(DarkWarrior(400, 960, p_texture));
    darkWarriors.push_back(DarkWarrior(752, 1040, p_texture));
    darkWarriors.push_back(DarkWarrior(1152, 850, p_texture));
    darkWarriors.push_back(DarkWarrior(1376, 860, p_texture));
    darkWarriors.push_back(DarkWarrior(1488, 688, p_texture));
    darkWarriors.push_back(DarkWarrior(1696, 688, p_texture));
    darkWarriors.push_back(DarkWarrior(2048, 560, p_texture));
    darkWarriors.push_back(DarkWarrior(2272, 450, p_texture));
    darkWarriors.push_back(DarkWarrior(3344, 640, p_texture));
    darkWarriors.push_back(DarkWarrior(4048, 288, p_texture));
    darkWarriors.push_back(DarkWarrior(4300, 800, p_texture));
    darkWarriors.push_back(DarkWarrior(4450, 540, p_texture));
    darkWarriors.push_back(DarkWarrior(4976, 580, p_texture));
    darkWarriors.push_back(DarkWarrior(5150, 580, p_texture));
    darkWarriors.push_back(DarkWarrior(5440, 700, p_texture));
}

void DarkWarriorFamily::show(RenderWindow &window, SDL_Rect &mCamera)
{
    for(int i = 0; i < darkWarriors.size(); i++)
    {
        darkWarriors[i].setMapXY(mCamera.x, mCamera.y);
        darkWarriors[i].show(window);
        darkWarriors[i].drawHP(*window.getRenderer(), mCamera);
    }
}

void DarkWarriorFamily::move(const SDL_Rect &player_box, Tile* map_data)
{
    for(int i = 0; i < darkWarriors.size(); i++)
    {
        darkWarriors[i].move(player_box, map_data);
    }
}

bool DarkWarriorFamily::isAttack(const Input &input, const SDL_Rect &player_box, const SDL_Rect &player_currentBox, const int &player_status)
{
    bool attacking = false;
    for(int i = 0; i < darkWarriors.size(); i++)
    {
        darkWarriors[i].isAttacked(input, player_box, player_currentBox, player_status);
        if(darkWarriors[i].isAttacking(input, player_box)) attacking = true;
    }
    return attacking;
}

void DarkWarriorFamily::checkDied()
{
    for(int i = 0; i < darkWarriors.size(); i++)
        while (i < darkWarriors.size() && darkWarriors[i].getDead())
        {
            darkWarriors.erase(darkWarriors.begin() + i);
            cntDarkWarriorDied++;
        }
}

bool DarkWarriorFamily::isWin()
{
    if(darkWarriors.size() == 0) return true;
    else return false;
}
