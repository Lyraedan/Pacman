#ifndef DRAWER_H
#define DRAWER_H

#include "GameImage.h"
#include <map>
#include <string>
#include <sstream>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class Drawer
{
public:
	static Drawer* Create(SDL_Window* window, SDL_Renderer* renderer);
	~Drawer(void);

	void DrawText(const char* text, const char* fontFile, int x, int y, SDL_Color color = { 255, 255, 255, 255 });
	
	void DrawResource(GameImage* resource, int x = 0, int y = 0);

	std::map<std::string, GameImage*> resources;

private:
	Drawer(SDL_Window* window, SDL_Renderer* renderer);
	bool Init();
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* world;
};

#endif // DRAWER_H