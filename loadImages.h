#ifndef LOADIMAGES_H_INCLUDED
#define LOADIMAGES_H_INCLUDED

#include "Header.h"

class loadImages{
public:
    loadImages();
    ~loadImages();

    void setRect(const int& x, const int& y) {rect.x = x, rect.y = y;}
    SDL_Rect getRect() const {return rect;}
    SDL_Texture* getTexture() const {return texture;}
    SDL_Texture* loadIMG(const string &filePath, SDL_Renderer* renderer);
    void renderTexture(SDL_Renderer* ren, const SDL_Rect* clip = nullptr);
    void Free();

private:
    SDL_Texture* texture;
    SDL_Rect rect;
};


#endif // LOADIMAGES_H_INCLUDED
