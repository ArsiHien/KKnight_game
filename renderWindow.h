#ifndef RENDERWINDOW_H_INCLUDED
#define RENDERWINDOW_H_INCLUDED

#include "Header.h"

class RenderWindow
{
public:
    void initWindow();
    void quitSDL();
    void clearScreen();
    void display();

    void logSDLError(ostream& os, const string &msg, bool fatal);

    SDL_Texture* loadIMG(const string &filePath);
    void renderTexture(SDL_Renderer* ren, const SDL_Rect* clip = nullptr);
    void render(SDL_Texture *mTexture, int x, int y, int realWidth, int realHeight, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
    SDL_Renderer* getRenderer() const
    {
        return m_renderer;
    };

protected:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
};

#endif // RENDERWINDOW_H_INCLUDED
