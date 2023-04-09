#include "renderWindow.h"

void RenderWindow::initWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError(cout, "SDL_Init", true);
    m_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (m_window == nullptr) logSDLError(cout, "CreateWindow", true);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (m_renderer == nullptr) logSDLError(cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(m_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void RenderWindow::quitSDL()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    m_window = nullptr;
    m_renderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}


void RenderWindow::clearScreen()
{
    SDL_RenderClear(m_renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(m_renderer);
}

void RenderWindow::logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
    return;
}

SDL_Texture* RenderWindow::loadIMG(const string &filePath)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface *loadedImage = IMG_Load(filePath.c_str());
    if(loadedImage != nullptr)
    {
        newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedImage);
        if (newTexture == nullptr)
        {
            logSDLError(cout, "CreateTextureFromSurface", true);
        }
        SDL_FreeSurface(loadedImage);
    }
    else
    {
        logSDLError(cout, "LoadIMG", true);
    }
    return newTexture;
}

void RenderWindow::render(SDL_Texture *mTexture, int x, int y, int realWidth, int realHeight, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = { x, y, realWidth, realHeight};
    SDL_RenderCopyEx( m_renderer, mTexture, clip, &renderQuad, angle, center, flip );
}
