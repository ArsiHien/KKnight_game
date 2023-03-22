#ifndef RENDERWINDOW_H_INCLUDED
#define RENDERWINDOW_H_INCLUDED

#include "Header.h"

class renderWindow{
public:
    void initWindow(SDL_Window* &window, SDL_Renderer* &renderer);
    void quitSDL();
    void clearScreen();
    void display();

    void logSDLError(ostream& os, const string &msg, bool fatal);

    void setRect(const int& x, const int& y) {rect.x = x, rect.y = y;}
    virtual SDL_Texture* loadIMG(const string &filePath, SDL_Renderer* renderer);
    void renderTexture(SDL_Renderer* ren, const SDL_Rect* clip = nullptr);
    void Free();

    SDL_Renderer* getRenderer() const {return g_renderer;};
    SDL_Rect getRect() const {return rect;}
    SDL_Texture* getTexture() const {return g_texture;}

protected:
    SDL_Window* g_window = nullptr;
    SDL_Renderer* g_renderer = nullptr;
    SDL_Texture* g_texture = nullptr;
    SDL_Rect rect;
};

#endif // RENDERWINDOW_H_INCLUDED
