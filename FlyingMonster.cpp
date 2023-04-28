#include "FlyingMonster.h"

FlyingMonster::FlyingMonster()
{
    HP = 250;
    on_ground = false;
    frame = 0;
    status = LEFT;
    mBox = {0, 0, 96, 96};
    input_type.left = 0;
    input_type.right = 0;
    //x_pos = 0; y_pos = 0;
    mVelX = 0;
    mVelY = 0;
    map_x = 0;
    map_y = 0;
    x_min = 0;
    x_max = 0;
    isDead = false;
    cntAttacking = 0;
    delay = 0;
    cntDead = 0;
    mTexture = nullptr;

    animations.push_back(idle);
    animations.push_back(run);
    animations.push_back(attack);
    animations.push_back(dead);
    animations.push_back(hurt);
}

FlyingMonster::~FlyingMonster()
{

}

void FlyingMonster::loadMonsterTexture(RenderWindow &window)
{
    mTexture = window.loadIMG("gfx/fm.png");
    if(mTexture == nullptr)
    {
        cout << "Failed to load fmonster texture\n";
    }
    //bull->mTexture = window.loadIMG("gfx/bullet.png");
//    if(bull->mTexture == nullptr){
//        cout << "Failed to load bullet texture\n";
//    }
}

void FlyingMonster::set_clips()
{
    int n = 0;
    for(int i = 0; i < (int)animations.size(); i++)
    {
        for(int j = 0; j < animations[i].amount_of_frame; j++)
        {
            Monster_Clips[n].x = j*animations[i].frame_width;
            Monster_Clips[n].y = (i+1)*96 - animations[i].frame_height;
            Monster_Clips[n].h = animations[i].frame_height;
            Monster_Clips[n].w = animations[i].frame_width;
            n++;
        }
    }
}

void FlyingMonster::set_x_pos(const int &xp)
{
    mBox.x = xp;
    x_min = xp - 100;
    x_max = xp + 100;
}
void FlyingMonster::show(RenderWindow &window)
{
    int dxr = 0, dxl = 0, dy = 0, slow = 1, t = 0;
//    mBox.x = mBox.x;
//    mBox.y = mBox.y;
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
            if(cntDead >= 14){
                isDead = true;
            }
            else{
                frame = dead.amount_of_frame*slow - 24;
                cntDead++;
            }
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
    SDL_Rect* current_clip = &Monster_Clips[t + frame/slow];
    if(status == LEFT)
    {
        window.render(mTexture, currentBox.x - dxl, currentBox.y - dy, currentBox.w, currentBox.h, current_clip);
    }
    else
    {
        window.render(mTexture, currentBox.x - dxr, currentBox.y - dy, currentBox.w, currentBox.h, current_clip, 0.0, NULL, SDL_FLIP_HORIZONTAL);
    }
}

void FlyingMonster::move(SDL_Rect player_box, Tile* map_data)
{
    mVelX = 0;
    mVelY += FMONSTER_GRAVITY_SPEED;
    if(mVelY >= FMONSTER_MAX_FALL_SPEED)
    {
        mVelY = FMONSTER_MAX_FALL_SPEED;
    }
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
        mVelX = -FMONSTER_SPEED;
    }
    else if(input_type.right == 1) mVelX = FMONSTER_SPEED;
    checkToMap(map_data);
}

void FlyingMonster::checkToMap(Tile *map_data)
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

bool FlyingMonster::checkCollision( SDL_Rect a, SDL_Rect b)
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

bool FlyingMonster::touchesWall(Tile *map_data)
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

void FlyingMonster::isAttacked(Input i, SDL_Rect player_box, SDL_Rect player_currentBox, int player_status)
{
    if(i.attack1 == 1 || i.attack2 == 1 || i.attack3 == 1)
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

bool FlyingMonster::isAttacking(Input i, SDL_Rect player_box)
{
    SDL_Rect Attack_box = {mBox.x + mBox.w/2 - attack.frame_width/2, mBox.y + mBox.h - attack.frame_height, attack.frame_width, attack.frame_height};
//    if(cntAttacking >= MAX_MONSTER_ATTACK){
//        delay++;
//        cout << delay << endl;
//        if(delay >= MAX_MONSTER_DELAY){
//            delay = 0;
//            cntAttacking = 0;
//        }
//        return false;
//    }
    if(checkCollision(Attack_box, player_box))
    {
        if(i.dead != 1)
        {
            input_type.attack = 1;
//            cntAttacking++;
        }
        if(input_type.hurt == 1) return false;
        if(i.defend == 0)
        {
            if(status == RIGHT)
            {
                if(player_box.x + 16 >= mBox.x + 32)
                {
                    return true;
                }
            }
            if(status == LEFT)
            {
                if(player_box.x + 16 <= mBox.x + 160)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void FlyingMonster::drawHP(SDL_Renderer &ren, SDL_Rect &mCamera)
{
    if(HP <= 0) return;
    SDL_Rect health_box = {mBox.x + mBox.w/2 - HP/10 - mCamera.x, mBox.y - 5 - mCamera.y, HP/5, 5};

    SDL_SetRenderDrawColor(&ren, 255, 0, 0, 255);
    SDL_RenderFillRect(&ren, &health_box);

    SDL_SetRenderDrawColor(&ren, 0, 0, 255, 255);
    SDL_RenderDrawRect(&ren, &health_box);
}
