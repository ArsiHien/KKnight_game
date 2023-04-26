#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <SDL.h>

class LTimer
{
private:
    Uint32 mStartTicks;
    Uint32 mPausedTicks;
    bool mStarted;
    bool mPaused;

public:
    LTimer();
    Uint32 getTicks();
    void start();
    void stop();
    void pause();
    void unpause();
    bool isPaused();
    bool isStarted();
};

#endif // TIMER_H_INCLUDED
