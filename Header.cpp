#include "Header.h"

void logSDLError(ostream& os, const string &msg, bool fatal){
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
    return;
}
