#ifndef INITWINDOW_H_INCLUDED
#define INITWINDOW_H_INCLUDED

#include "Header.h"

class initWindow
{
public:
    initWindow(const string WINDOW_TITLE, const int SCREEN_HEIGHT, const int SCREEN_WIDTH);
    void quitSDL();
    void clearScreen();
    void display();
};

#endif // INITWINDOW_H_INCLUDED
