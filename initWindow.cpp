#include "initWindow.h"
#include "Header.h"
initWindow::initWindow(const string WINDOW_TITLE, const int SCREEN_HEIGHT, const int SCREEN_WIDTH)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError(cout, "SDL_Init", true);
    g_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (g_window == nullptr) logSDLError(cout, "CreateWindow", true);

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (g_renderer == nullptr) logSDLError(cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void initWindow::quitSDL()
{
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}


void initWindow::clearScreen()
{
    SDL_RenderClear(g_renderer);
}

void initWindow::display()
{
    SDL_RenderPresent(g_renderer);
}
