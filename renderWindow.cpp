#include "renderWindow.h"

bool RenderWindow::initWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(cout, "SDL_Init", true);
        return false;
    }
    m_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (m_window == nullptr)
    {
        logSDLError(cout, "CreateWindow", true);
        return false;
    }
    SDL_Surface *icon = IMG_Load("gfx/icon.png");
            SDL_SetWindowIcon(m_window, icon);
            SDL_FreeSurface(icon);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);

    if (m_renderer == nullptr)
    {
        logSDLError(cout, "CreateRenderer", true);
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(m_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        logSDLError(cout, "InitMixer", true);
        return false;
    }
    if (TTF_Init() == -1)
    {
        printf("Failed to init SDL_ttf, error: %s\n", TTF_GetError());
        return false;
    }
    return true;
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

void RenderWindow::render(SDL_Texture *mTexture, const int &x, const int &y, const int &realWidth, const int &realHeight, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = { x, y, realWidth, realHeight};
    SDL_RenderCopyEx( m_renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

void RenderWindow::renderB(SDL_Texture *mTexture, SDL_Rect* box, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(m_renderer, mTexture, clip, box, angle, center, flip);
}

void RenderWindow::renderBox(SDL_Rect* box)
{
    SDL_SetRenderDrawColor(m_renderer, 0, 250, 154, 255);
    SDL_RenderDrawRect(m_renderer, box);
}

void RenderWindow::renderText(const char *text, TTF_Font *font, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Color textColor = {r, g, b, a};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == NULL)
    {
        printf("Failed to create text surface, error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    if (textTexture == NULL)
    {
        printf("Failed to create texture, error: %s\n", SDL_GetError());
        return;
    }
    SDL_Rect textRect = {x, y, 0, 0};
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h); // lấy kích thước của texture
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
