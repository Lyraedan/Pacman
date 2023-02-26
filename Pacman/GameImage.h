#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class GameImage
{
	// Used for loading resources once and batching them
public:
	GameImage(const char* imgDir, SDL_Renderer* renderer) {
		surface = IMG_Load(imgDir);
		optimizedSurface = SDL_CreateTextureFromSurface(renderer, surface);

		sizeRect.x = 0;
		sizeRect.y = 0;
		sizeRect.w = surface->w;
		sizeRect.h = surface->h;
	}

	SDL_Surface* surface;
	SDL_Texture* optimizedSurface;
	SDL_Rect sizeRect;

	void Release();
};