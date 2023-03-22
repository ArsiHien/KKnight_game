#include "loadImages.h"
#include "Header.h"

loadImages::loadImages(){
    texture = nullptr;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

loadImages::~loadImages(){
    Free();
}


SDL_Texture* loadImages::loadIMG(const string &filePath, SDL_Renderer* renderer){
    SDL_Texture* newTexture = nullptr;
    SDL_Surface *loadedImage = IMG_Load(filePath.c_str());
    if(loadedImage != nullptr){
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		if (newTexture == nullptr){
			logSDLError(cout, "CreateTextureFromSurface", true);
		}
		else{
            rect.w = loadedImage -> w;
            rect.h = loadedImage -> h;
		}
		SDL_FreeSurface(loadedImage);
    }
    else {
		logSDLError(cout, "LoadIMG", true);
	}
	return newTexture;
}

void loadImages::renderTexture(SDL_Renderer* ren, const SDL_Rect* clip){
    SDL_Rect dst = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopy(ren, texture, clip, &dst);
}

void loadImages::Free(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
        rect.w = 0;
        rect.h = 0;
    }
}

