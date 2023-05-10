#include "Boss.h"

Boss::Boss(const int &xp, const int &yp, SDL_Texture *p_texture)
{
    mTexture = p_texture;
    HP = 1000;
    on_ground = false;
    frame = 0;
    sFrame = 0;
    status = LEFT;
    mBox = {xp, yp, 256, 256};
    rPlayerBox = mBox;
    x_min = xp - 500;
    x_max = xp + 500;
    input_type.left = 0;
    input_type.right = 0;
    mVelX = 0;
    mVelY = 0;
    isDead = false;
    hitting = false, skillHitting = false;
    thinkTime = SCREEN_FPS*2;
    skillTime = SCREEN_FPS*7;
    animations.push_back(idle);
    animations.push_back(run);
    animations.push_back(attack);
    animations.push_back(hurt);
    animations.push_back(dead);
    animations.push_back(cast);
    animations.push_back(spell);
    set_clips();
}

Boss::~Boss()
{

}

void Boss::set_clips()
{
    int n = 0;
    for(int i = 0; i < (int)animations.size(); i++)
    {
        for(int j = 0; j < animations[i].amount_of_frame; j++)
        {
            Boss_Clips[n].x = j*animations[i].frame_width;
            Boss_Clips[n].y = (i+1)*384 - animations[i].frame_height;
            Boss_Clips[n].h = animations[i].frame_height;
            Boss_Clips[n].w = animations[i].frame_width;
            n++;
        }
    }
}

void Boss::show(RenderWindow &window, SDL_Rect player_box)
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
            frame = dead.amount_of_frame*slow;
            isDead = true;
        }
    }
    else if(input_type.skills1 == 1)
    {
        input_type.hurt = 0;
        dxr = cast.denta_x_right, dxl = cast.denta_x_left, dy = cast.denta_y;
        slow = cast.slow_down;
        currentBox.w = cast.frame_width;
        currentBox.h = cast.frame_height;
        for(int i = 0; i <cast.index; i++)
        {
            t += animations[i].amount_of_frame;
        }
        frame++;
        if(frame >= cast.amount_of_frame*slow)
        {
            frame = 0;
            sFrame = 0;
            input_type.skills1 = 0;
            input_type.skills2 = 1;
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
        if(frame >= 5*attack.slow_down && frame <= 5*attack.slow_down + 8)
        {
            hitting = true;
        }
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
    SDL_Rect* current_clip = &Boss_Clips[t + frame/slow];
    SDL_Rect b = {currentBox.x - dxl, currentBox.y - dy, currentBox.w, currentBox.h};
    if(status == LEFT)
    {
        window.render(mTexture, currentBox.x - dxl, currentBox.y - dy, currentBox.w, currentBox.h, current_clip);
    }
    else
    {
        window.render(mTexture, currentBox.x - dxr, currentBox.y - dy, currentBox.w, currentBox.h, current_clip, 0.0, NULL, SDL_FLIP_HORIZONTAL);
    }
}

void Boss::move(const SDL_Rect &player_box, Tile* map_data)
{
    if(skillTime == 0) return;
    mVelX = 0;
    mVelY += BOSS_GRAVITY_SPEED;
    if(mVelY >= BOSS_MAX_FALL_SPEED)
    {
        mVelY = BOSS_MAX_FALL_SPEED;
    }
    if(input_type.skills1 == 0)
    {
        input_type.run = 1;
        input_type.right = 0;
        input_type.left = 0;
        int distance = sqrt(min(pow((x_min - player_box.x + player_box.w/2),2), pow((x_max - player_box.x + player_box.w/2),2)) + pow((mBox.y + mBox.h/2 - player_box.y + player_box.h/2), 2));
        if(mBox.x >= x_min && mBox.x <= x_max && distance <= 1024 && abs(player_box.x + player_box.w - mBox.x - mBox.w) > mBox.w/2)
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
        else if(distance > 1024 || abs(player_box.x + player_box.w - mBox.x - mBox.w) <= mBox.w/2) input_type.run = 0;
        if(input_type.attack == 1) mVelX = 0;
        else if(input_type.left == 1)
        {
            mVelX = -BOSS_SPEED;
        }
        else if(input_type.right == 1) mVelX = BOSS_SPEED;
    }
    else input_type.run = 0;
    checkToMap(map_data);
}

void Boss::checkToMap(Tile *map_data)
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

bool Boss::checkCollision( SDL_Rect a, SDL_Rect b)
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

bool Boss::touchesWall(Tile *map_data)
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

void Boss::isAttacked(const Input &input, const SDL_Rect &player_box, const SDL_Rect &player_currentBox, const int &player_status)
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
            if(player_box.x + player_box.w/2 >= mBox.x + mBox.w/2 - 15 && checkCollision(mBox, player_currentBox))
            {
                input_type.hurt = 1;
                HP--;
            }
        }
    }
}

bool Boss::isAttacking(const Input &input, SDL_Rect player_box)
{
    if(input_type.hurt == 1) return false;
    Attack_box = {mBox.x + mBox.w/2 - attack.frame_width/2, mBox.y + mBox.h - attack.frame_height, attack.frame_width, attack.frame_height};
    if(thinkTime > 0)
    {
        thinkTime--;
        if(checkCollision(Attack_box, player_box))
        {

            if(input.defend == 0)
            {
                if(status == RIGHT)
                {
                    if(player_box.x + 16 >= mBox.x + 176)
                    {
                        return hitting;
                    }
                    else return false;
                }
                if(status == LEFT)
                {
                    if(player_box.x + 16 <= mBox.x)
                    {
                        return hitting;
                    }
                    else return false;
                }
            }
        }
    }
    if(input_type.skills1 == 1) return false;
    if(checkCollision(Attack_box, player_box))
    {
        if(input.dead != 1)
        {
            input_type.attack = 1;
            frame = 0;
            thinkTime = SCREEN_FPS*2;
        }
        if(input.defend == 0)
        {
            if(status == RIGHT)
            {
                if(player_box.x + 16 >= mBox.x + 176)
                {
                    return hitting;
                }
                else return false;
            }
            if(status == LEFT)
            {
                if(player_box.x + 16 <= mBox.x)
                {
                    return hitting;
                }
                else return false;
            }
        }
    }
    return false;
}

bool Boss::isAttacking2(const Input &input, SDL_Rect player_box)
{
    SDL_Rect Attack_box = {mBox.x - SCREEN_WIDTH, mBox.y - SCREEN_HEIGHT/2, 2*SCREEN_WIDTH, mBox.h + SCREEN_HEIGHT/2};
    if(skillTime > 0)
    {
        skillTime--;
        if(!checkCollision(Attack_box, player_box)) return false;
        return skillHitting;
    }

    if(checkCollision(Attack_box, player_box))
    {
        if(input.dead != 1)
        {
            input_type.skills1 = 1;
            skillTime = SCREEN_FPS*7;
        }
        return skillHitting;
    }
    return false;
}

void Boss::showSkillBoss(RenderWindow &window, SDL_Rect player_box, SDL_Rect mCamera)
{
    if(input_type.skills2 == 0) return;
    if(sFrame == 0)
    {
        rPlayerBox.x = player_box.x;
        rPlayerBox.y = player_box.y;
    }
    sFrame++;
    if(sFrame%4 == 0 && sFrame >= 7*spell.slow_down && sFrame <= 12*spell.slow_down && (rPlayerBox.x + 64 - 80 <= (player_box.x + player_box.w/2)) && (rPlayerBox.x + 64 + 128 - 80 >= (player_box.x + player_box.w/2)))
    {
        skillHitting = true;
    }
    else skillHitting = false;
    if(sFrame >= spell.amount_of_frame*spell.slow_down)
    {
        sFrame = 0;
        input_type.skills2 = 0;
        return;
    }
    int t = 0;
    for(int i = 0; i < spell.index; i++)
    {
        t += animations[i].amount_of_frame;
    }
    window.render(mTexture, rPlayerBox.x - mCamera.x - 80, rPlayerBox.y - mCamera.y - 170, rPlayerBox.w, rPlayerBox.h, &Boss_Clips[t + sFrame/spell.slow_down]);
}

void Boss::drawHP(SDL_Renderer &ren, SDL_Rect &mCamera)
{
    if(HP <= 0) return;
    SDL_Rect health_box = {mBox.x + mBox.w/2 - HP/10 - mCamera.x, mBox.y - 5 - mCamera.y, HP/5, 5};

    SDL_SetRenderDrawColor(&ren, 255, 0, 0, 255);
    SDL_RenderFillRect(&ren, &health_box);

    SDL_SetRenderDrawColor(&ren, 0, 0, 255, 255);
    SDL_RenderDrawRect(&ren, &health_box);
}
