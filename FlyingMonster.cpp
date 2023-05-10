#include "FlyingMonster.h"

Bullet::Bullet(const int &x, const int &y,SDL_Texture *p_texture, SDL_Texture *e_tex, const int &monster_status)
{
    mTexture = p_texture;
    eTexture = e_tex;
    mVelX = 3;
    frame = 0, eFrame = 0;
    setClips();
    life = SCREEN_FPS*2;
    mStatus = monster_status;
    hitting = false;
    if(mStatus == RIGHT)
    {
        mBox = {x + 50, y + 30, BULLET_WIDTH, BULLET_HEIGHT};
        xp = x + 30;
    }
    else
    {
        mBox = {x, y + 30, BULLET_WIDTH, BULLET_HEIGHT};
        xp = x;
    }
    rBox = mBox;
}

void Bullet::setClips()
{
    for(int i = 0, x = 0, y = 0; i < BULLET_FRAMES; i++)
    {
        mClips[i] = {x, y, BULLET_TEXTURE_WIDTH, BULLET_TEXTURE_HEIGHT};
        x += BULLET_TEXTURE_WIDTH;
    }
    for(int i = 0, x = 0, y = 0; i < TOTAL_EXPLOSION_FRAME; i++, x += EXPLOSION_TEXTURE_WIDTH)
    {
        m_explosionClips[i] = {x, y, EXPLOSION_TEXTURE_WIDTH, EXPLOSION_TEXTURE_HEIGHT};
    }
}

void Bullet::handleMove(SDL_Rect &mCamera)
{
    if(hitting)
    {
        eFrame++;
        mBox.x = xp;
        rBox.x = xp - mCamera.x;
        if(eFrame >= TOTAL_EXPLOSION_FRAME*4)
        {
            eFrame = 0;
            life = 0;
        }
    }
    else
    {
        if(mStatus == RIGHT) xp += mVelX;
        else xp -= mVelX;
        mBox.x = xp;
        rBox.x = xp - mCamera.x;
        rBox.y = mBox.y - mCamera.y;
        frame++;
        if(frame >= BULLET_FRAMES*8) frame = 0;
        life--;
    }

}

void Bullet::render(RenderWindow &window)
{
    if(hitting)
    {
        if(mStatus == RIGHT) window.render(eTexture, rPlayerBox.x + 5, rPlayerBox.y + 8, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, &m_explosionClips[eFrame/4]);
        else window.render(eTexture, rPlayerBox.x + 20, rPlayerBox.y + 8, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, &m_explosionClips[eFrame/4], 0, 0, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        if(mStatus == RIGHT) window.renderB(mTexture, &rBox, &mClips[frame/8]);
        else window.renderB(mTexture, &rBox, &mClips[frame/8], 0, 0, SDL_FLIP_HORIZONTAL);
    }
}

bool Bullet::isHitting(Input i, SDL_Rect player_box, SDL_Rect &mCamera, int player_status)
{
    if(eFrame == 0) firstTouch = player_box;
    rPlayerBox = {player_box.x - mCamera.x, player_box.y - mCamera.y, player_box.w, player_box.h};
    if(checkCollision(mBox, firstTouch))
    {
        if(eFrame >= TOTAL_EXPLOSION_FRAME*4)
        {
            eFrame = 0;
        }
        hitting = true;
        if(i.defend == 1 && (mStatus != player_status))
        {
            life = 0;
            return false;
        }
        if(eFrame == 10)
        {
            return true;
        }
        else return false;
    }
    return false;
}

bool Bullet::checkCollision( SDL_Rect a, SDL_Rect b)
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

FlyingMonster::FlyingMonster(const int &xp, const int &yp, SDL_Texture *p_texture, SDL_Texture *b_texture, SDL_Texture *e_texture)
{
    mTexture = p_texture;
    bTexture = b_texture;
    eTexture = e_texture;
    HP = 200;
    on_ground = false;
    frame = 0;
    status = LEFT;
    mBox = {xp, yp, 96, 96};
    x_min = xp - 100;
    x_max = xp + 100;
    input_type.left = 0;
    input_type.right = 0;
    mVelX = 0;
    mVelY = 0;
    map_x = 0;
    map_y = 0;
    isDead = false;
    thinkTime = SCREEN_FPS*3/2;
    BullHitting = false;
    animations.push_back(idle);
    animations.push_back(run);
    animations.push_back(attack);
    animations.push_back(hurt);
    animations.push_back(dead);

    set_clips();
}

FlyingMonster::~FlyingMonster()
{
//    delete mBulletList;
//    SDL_DestroyTexture(bTexture);
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
void FlyingMonster::show(RenderWindow &window, SDL_Rect &mCamera, const Input &input, const SDL_Rect &player_box, int player_status, GameState &state)
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
            isDead = true;
//            if(cntDead >= 14){
//                isDead = true;
//            }
//            else{
//                frame = dead.amount_of_frame*slow - 24;
//                cntDead++;
//            }
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
        if(input_type.attack == 0)
        {
            Bullet *b = new Bullet(mBox.x, mBox.y, bTexture, eTexture, status);
            bullets.push_back(b);
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
    if(state == STATE_PLAY) handleBullets(window, mCamera, status, input, player_box, player_status);
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

void FlyingMonster::move(const SDL_Rect &player_box, Tile* map_data)
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

bool FlyingMonster::isAttacking(const Input &i, const SDL_Rect &player_box)
{
    if(BullHitting)
    {
        BullHitting = false;
        return true;
    }
    if(HP <= 0) return false;
    if(thinkTime > 0)
    {
        thinkTime--;
        return false;
    }
    SDL_Rect Attack_box = {mBox.x - SCREEN_WIDTH/3, mBox.y - SCREEN_WIDTH/6, SCREEN_WIDTH*3/2, SCREEN_WIDTH/3};
    if(checkCollision(Attack_box, player_box))
    {
        if(i.dead != 1)
        {
            input_type.attack = 1;
            frame = 0;
            thinkTime = SCREEN_FPS*3/2;
        }
        if(input_type.hurt == 1) return false;
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

void FlyingMonster::handleBullets(RenderWindow &window, SDL_Rect &mCamera, const int &monster_status, const Input &input, const SDL_Rect &player_box, int player_status)
{
    for(int i = 0; i < bullets.size(); i++)
    {
        Bullet* bull = bullets.at(i);
        if(bull != nullptr)
        {
            if(bull->getLife() > 0)
            {
                if(bull->isHitting(input, player_box, mCamera, player_status)) BullHitting = true;
                bull->handleMove(mCamera);
                bull->render(window);
            }
            else
            {
                bullets.erase(bullets.begin() + i);
                if(bull != nullptr)
                {
                    delete bull;
                    bull = nullptr;
                }
            }
        }
    }
}

FlyingMonsterFamily::FlyingMonsterFamily(SDL_Texture *p_texture, SDL_Texture *b_texture, SDL_Texture *e_texture)
{
    FlyingMonsters.push_back(FlyingMonster(944, 1040, p_texture, b_texture, e_texture));
    FlyingMonsters.push_back(FlyingMonster(1888, 560, p_texture, b_texture, e_texture));
    FlyingMonsters.push_back(FlyingMonster(2500, 480, p_texture, b_texture, e_texture));
    FlyingMonsters.push_back(FlyingMonster(2752, 500, p_texture, b_texture, e_texture));
    FlyingMonsters.push_back(FlyingMonster(2944, 560, p_texture, b_texture, e_texture));
    FlyingMonsters.push_back(FlyingMonster(3680, 480, p_texture, b_texture, e_texture));
    FlyingMonsters.push_back(FlyingMonster(4400, 672, p_texture, b_texture, e_texture));
    FlyingMonsters.push_back(FlyingMonster(4720, 380, p_texture, b_texture, e_texture));

}

void FlyingMonsterFamily::show(RenderWindow &window, SDL_Rect &mCamera, const Input &input, const SDL_Rect &player_box, int player_status, GameState &state)
{
    for(int i = 0; i < FlyingMonsters.size(); i++)
    {
        FlyingMonsters[i].setMapXY(mCamera.x, mCamera.y);
        FlyingMonsters[i].show(window, mCamera, input, player_box, player_status, state);
        FlyingMonsters[i].drawHP(*window.getRenderer(), mCamera);
    }
}

void FlyingMonsterFamily::move(const SDL_Rect &player_box, Tile* map_data)
{
    for(int i = 0; i < FlyingMonsters.size(); i++)
    {
        FlyingMonsters[i].move(player_box, map_data);
    }
}

bool FlyingMonsterFamily::isAttack(const Input &input, const SDL_Rect &player_box, const SDL_Rect &player_currentBox, const int &player_status)
{
    bool attacking = false;
    for(int i = 0; i < FlyingMonsters.size(); i++)
    {
        FlyingMonsters[i].isAttacked(input, player_box, player_currentBox, player_status);
        if(FlyingMonsters[i].isAttacking(input, player_box)) attacking = true;
    }
    return attacking;
}

void FlyingMonsterFamily::checkDied()
{
    for(int i = 0; i < FlyingMonsters.size(); i++)
        while (i < FlyingMonsters.size() && FlyingMonsters[i].getDead())
        {
            FlyingMonsters.erase(FlyingMonsters.begin() + i);
            cntDarkWarriorDied++;
        }
}

bool FlyingMonsterFamily::isWin()
{
    if(FlyingMonsters.size() == 0) return true;
    else return false;
}
