#include "renderWindow.h"

void renderWindow::initWindow(SDL_Window* &window, SDL_Renderer* &renderer)
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

void renderWindow::quitSDL()
{
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

	g_window = nullptr;
	g_renderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}


void renderWindow::clearScreen()
{
    SDL_RenderClear(g_renderer);
}

void renderWindow::display()
{
    SDL_RenderPresent(g_renderer);
}

void renderWindow::logSDLError(ostream& os, const string &msg, bool fatal){
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
    return;
}

SDL_Texture* renderWindow::loadIMG(const string &filePath, SDL_Renderer* ren){
    Free();
    SDL_Texture* newTexture = nullptr;
    SDL_Surface *loadedImage = IMG_Load(filePath.c_str());
    if(loadedImage != nullptr){
        newTexture = SDL_CreateTextureFromSurface(ren, loadedImage);
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
	g_texture = newTexture;
	return g_texture;
}

void renderWindow::renderTexture(SDL_Renderer* ren, const SDL_Rect* clip){
    SDL_Rect dst = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopy(ren, g_texture, clip, &dst);
}

void renderWindow::Free(){
    if(g_texture != nullptr){
        SDL_DestroyTexture(g_texture);
        g_texture = nullptr;
        rect.w = 0;
        rect.h = 0;
    }
}
