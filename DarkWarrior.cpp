//#include "DarkWarrior.h"
//
//DarkWarrior::DarkWarrior(){
//
//}
//
//DarkWarrior::~DarkWarrior(){
//
//}
//
//void DarkWarrior::show(RenderWindow &window){
//    int dxr = 0, dxl = 0, dy = 0, slow = 1, t = 0;
////    mBox.x = mBox.x;
////    mBox.y = mBox.y;
//    currentBox.x = mBox.x - map_x;
//    currentBox.y = mBox.y - map_y;
//    if(HP <= 0)
//    {
//        dxr = dead.denta_x_right, dxl = dead.denta_x_left, dy = dead.denta_y;
//        slow = dead.slow_down;
//        currentBox.w = dead.frame_width;
//        currentBox.h = dead.frame_height;
//        for(int i = 0; i <dead.index; i++)
//        {
//            t += animations[i].amount_of_frame;
//        }
//        frame++;
//        if(frame >= dead.amount_of_frame*slow)
//        {
//            frame = 0;
//            isDead = true;
//        }
//    }
//    else if(input_type.hurt == 1)
//    {
//        dxr = hurt.denta_x_right, dxl = hurt.denta_x_left, dy = hurt.denta_y;
//        slow = hurt.slow_down;
//        currentBox.w = hurt.frame_width;
//        currentBox.h = hurt.frame_height;
//        for(int i = 0; i <hurt.index; i++)
//        {
//            t += animations[i].amount_of_frame;
//        }
//        frame++;
//        if(frame >= hurt.amount_of_frame*slow)
//        {
//            frame = 0;
//            input_type.hurt = 0;
//        }
//    }
//    else if(input_type.attack == 1)
//    {
//        dxr = attack.denta_x_right, dxl = attack.denta_x_left, dy = attack.denta_y;
//        slow = attack.slow_down;
//        currentBox.w = attack.frame_width;
//        currentBox.h = attack.frame_height;
//        for(int i = 0; i <attack.index; i++)
//        {
//            t += animations[i].amount_of_frame;
//        }
//        frame++;
//        if(frame >= attack.amount_of_frame*slow)
//        {
//            frame = 0;
//            input_type.attack = 0;
//        }
//    }
//    else if(input_type.run == 1)
//    {
//        dxr = run.denta_x_right, dxl = run.denta_x_left, dy = run.denta_y;
//        slow = run.slow_down;
//        currentBox.w = run.frame_width;
//        currentBox.h = run.frame_height;
//        for(int i = 0; i <run.index; i++)
//        {
//            t += animations[i].amount_of_frame;
//        }
//        frame = ++frame%(run.amount_of_frame*slow);
//    }
//    else
//    {
//        dxr = idle.denta_x_right, dxl = idle.denta_x_left, dy = idle.denta_y;
//        slow = idle.slow_down;
//        currentBox.w = idle.frame_width;
//        currentBox.h = idle.frame_height;
//        for(int i = 0; i <idle.index; i++)
//        {
//            t += animations[i].amount_of_frame;
//        }
//        frame++;
//        if(frame >= idle.amount_of_frame*slow)
//        {
//            frame = 0;
//        }
//    }
//    SDL_Rect* current_clip = &Monster_Clips[t + frame/slow];
//    if(status == LEFT)
//    {
//        window.render(mTexture, currentBox.x - dxl, currentBox.y - dy, currentBox.w, currentBox.h, current_clip);
//    }
//    else
//    {
//        window.render(mTexture, currentBox.x - dxr, currentBox.y - dy, currentBox.w, currentBox.h, current_clip, 0.0, NULL, SDL_FLIP_HORIZONTAL);
//    }
//}
