#ifndef IMPTIMER_H_INCLUDED
#define IMPTIMER_H_INCLUDED

#include "Header.h"

class ImpTimer{
public:
    ImpTimer();
    ~ImpTimer();
    void start();
    void stop();
    void paused();
    void unpaused();
    int get_ticks();
    bool is_started();
    bool is_paused();

private:
    int start_tick;
    int paused_tick;
    bool is_paused_;
    bool is_started_;
};

#endif // IMPTIMER_H_INCLUDED
