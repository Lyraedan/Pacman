#include "GameImage.h"

void GameImage::Release()
{
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
}
