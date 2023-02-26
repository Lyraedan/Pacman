#ifndef DRAWER_H
#define DRAWER_H

#include "GameImage.h"
#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class Drawer
{
public:
	static Drawer* Create(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Drawer(void);

	void DrawText(const char* aText, const char* aFontFile, int aX, int aY);
	
	void DrawResource(GameImage* resource, int x = 0, int y = 0);

	std::map<std::string, GameImage*> resources;

private:
	Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	bool Init();
	
	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
	SDL_Surface* world;
};

#endif // DRAWER_H