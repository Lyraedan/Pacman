#include "Drawer.h"

Drawer* Drawer::Create(SDL_Window* aWindow, SDL_Renderer* aRenderer)
{
	Drawer* drawer = new Drawer(aWindow, aRenderer);

	if (!drawer->Init())
	{
		delete drawer;
		drawer = NULL;
	}

	return drawer;
}

Drawer::Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer)
: myWindow(aWindow)
, myRenderer(aRenderer)
{
}

Drawer::~Drawer(void)
{

}

bool Drawer::Init()
{
	if (!myWindow)
		return false;

	// Misc
	resources["map"] = new GameImage("playfield.png", myRenderer);
	resources["dot"] = new GameImage("small_dot.png", myRenderer);
	resources["bigdot"] = new GameImage("big_dot.png", myRenderer);
	resources["cherry"] = new GameImage("cherry.png", myRenderer);
	resources["title"] = new GameImage("title.png", myRenderer);
	resources["win"] = new GameImage("win.png", myRenderer);
	resources["gameover"] = new GameImage("gameover.png", myRenderer);

	// Debugging
	resources["target"] = new GameImage("path_dest.png", myRenderer);
	resources["target_path"] = new GameImage("path_next.png", myRenderer);
	
	// Ghosts
	resources["ghost_dead"] = new GameImage("Ghost_Dead_32.png", myRenderer);

	resources["ghost_vulnerable"] = new GameImage("ghost_vulnerable.png", myRenderer);
	resources["ghost_vulnerable_eyes"] = new GameImage("ghost_vulnerable_eyes.png", myRenderer);
	resources["ghost_vulnerable_feet_a"] = new GameImage("ghost_vulnerable_feet_a.png", myRenderer);
	resources["ghost_vulnerable_feet_b"] = new GameImage("ghost_vulnerable_feet_b.png", myRenderer);

	resources["ghost_vulnerable_warning"] = new GameImage("ghost_vulnerable_warning.png", myRenderer);
	resources["ghost_vulnerable_warning_eyes"] = new GameImage("ghost_vulnerable_warning_eyes.png", myRenderer);
	resources["ghost_vulnerable_warning_feet_a"] = new GameImage("ghost_vulnerable_warning_feet_a.png", myRenderer);
	resources["ghost_vulnerable_warning_feet_b"] = new GameImage("ghost_vulnerable_warning_feet_b.png", myRenderer);

	resources["ghost_eyes_right"] = new GameImage("eyes_right.png", myRenderer);
	resources["ghost_eyes_left"] = new GameImage("eyes_left.png", myRenderer);
	resources["ghost_eyes_up"] = new GameImage("eyes_up.png", myRenderer);
	resources["ghost_eyes_down"] = new GameImage("eyes_down.png", myRenderer);

	resources["ghost_shadow"] = new GameImage("shadow.png", myRenderer);
	resources["ghost_shadow_feet_a"] = new GameImage("shadow_feet_a.png", myRenderer);
	resources["ghost_shadow_feet_b"] = new GameImage("shadow_feet_b.png", myRenderer);

	resources["ghost_speedy"] = new GameImage("speedy.png", myRenderer);
	resources["ghost_speedy_feet_a"] = new GameImage("speedy_feet_a.png", myRenderer);
	resources["ghost_speedy_feet_b"] = new GameImage("speedy_feet_b.png", myRenderer);

	resources["ghost_bashful"] = new GameImage("bashful.png", myRenderer);
	resources["ghost_bashful_feet_a"] = new GameImage("bashful_feet_a.png", myRenderer);
	resources["ghost_bashful_feet_b"] = new GameImage("bashful_feet_b.png", myRenderer);

	resources["ghost_pokey"] = new GameImage("pokey.png", myRenderer);
	resources["ghost_pokey_feet_a"] = new GameImage("pokey_feet_a.png", myRenderer);
	resources["ghost_pokey_feet_b"] = new GameImage("pokey_feet_b.png", myRenderer);

	// Pacman
	// Open
	resources["pacman_right_open"] = new GameImage("open_right.png", myRenderer);
	resources["pacman_left_open"] = new GameImage("open_left.png", myRenderer);
	resources["pacman_up_open"] = new GameImage("open_up.png", myRenderer);
	resources["pacman_down_open"] = new GameImage("open_down.png", myRenderer);

	// Closed
	resources["pacman_right_closed"] = new GameImage("closed_right_32.png", myRenderer);
	resources["pacman_left_closed"] = new GameImage("closed_left_32.png", myRenderer);
	resources["pacman_up_closed"] = new GameImage("closed_up_32.png", myRenderer);
	resources["pacman_down_closed"] = new GameImage("closed_down_32.png", myRenderer);

	// Transition
	resources["pacman_transition_right"] = new GameImage("transition_right.png", myRenderer);
	resources["pacman_transition_left"] = new GameImage("transition_left.png", myRenderer);
	resources["pacman_transition_up"] = new GameImage("transition_up.png", myRenderer);
	resources["pacman_transition_down"] = new GameImage("transition_down.png", myRenderer);

	// Death animation
	resources["pacman_death_0"] = new GameImage("death_0.png", myRenderer);
	resources["pacman_death_1"] = new GameImage("death_1.png", myRenderer);
	resources["pacman_death_2"] = new GameImage("death_2.png", myRenderer);
	resources["pacman_death_3"] = new GameImage("death_3.png", myRenderer);
	resources["pacman_death_4"] = new GameImage("death_4.png", myRenderer);
	resources["pacman_death_5"] = new GameImage("death_5.png", myRenderer);
	resources["pacman_death_6"] = new GameImage("death_6.png", myRenderer);
	resources["pacman_death_7"] = new GameImage("death_7.png", myRenderer);
	resources["pacman_death_8"] = new GameImage("death_8.png", myRenderer);
	resources["pacman_death_9"] = new GameImage("death_9.png", myRenderer);
	resources["pacman_death_10"] = new GameImage("death_10.png", myRenderer);
	resources["pacman_death_11"] = new GameImage("death_11.png", myRenderer);


	return true;
}

void Drawer::DrawText(const char* aText, const char* aFontFile, int aX, int aY, SDL_Color fg)
{
	TTF_Font* font=TTF_OpenFont(aFontFile, 24);

	SDL_Surface* surface = TTF_RenderText_Solid(font, aText, fg);

	if (surface == NULL)
		return;

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(myRenderer, surface);

    SDL_Rect sizeRect;
    sizeRect.x = 0 ;
    sizeRect.y = 0 ;
    sizeRect.w = surface->w ;
    sizeRect.h = surface->h ;

    SDL_Rect posRect ;
    posRect.x = aX;
    posRect.y = aY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(myRenderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void Drawer::DrawResource(GameImage* resource, int x, int y)
{
	if (resource == NULL)
		return;

	SDL_Rect posRect;
	posRect.x = x;
	posRect.y = y;
	posRect.w = resource->sizeRect.w;
	posRect.h = resource->sizeRect.h;
	SDL_RenderCopy(myRenderer, resource->optimizedSurface, &resource->sizeRect, &posRect);
}
