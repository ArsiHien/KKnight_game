#include "danBan.h"

danBan::danBan(){
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
}

danBan::~danBan(){

}

void danBan::handleMove(const int& x_border, const int& y_border){
    rect.x += x_val_;
    if(rect.x > x_border){
        is_move_ = false;
    }
}
