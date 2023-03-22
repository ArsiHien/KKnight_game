#ifndef DANBAN_H_INCLUDED
#define DANBAN_H_INCLUDED

#include "Header.h"
#include "renderWindow.h"

class danBan : public renderWindow{
public:
    danBan();
    ~danBan();

    void set_x_val(const int& x_val) {x_val_ = x_val;}
    void set_y_val(const int& y_val) {y_val_ = y_val;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move(const bool& is_move) {is_move_ = is_move;}
    bool get_is_move() const {return is_move_;}

    void handleMove(const int& x_border, const int& y_border);
private:
    int x_val_;
    int y_val_;
    bool is_move_;

};

#endif // DANBAN_H_INCLUDED
