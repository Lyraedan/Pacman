#include "Drawer.h"

Drawer* Drawer::Create(SDL_Window* window, SDL_Renderer* renderer)
{
	Drawer* drawer = new Drawer(window, renderer);

	if (!drawer->Init())
	{
		delete drawer;
		drawer = NULL;
	}

	return drawer;
}

Drawer::Drawer(SDL_Window* window, SDL_Renderer* renderer)
{
	this->window = window;
	this->renderer = renderer;
}

Drawer::~Drawer(void)
{

}

bool Drawer::Init()
{
	// If window is NULL
	if (!window)
		return false;

	// Misc
	resources["map"] = new GameImage("playfield.png", renderer);
	resources["dot"] = new GameImage("small_dot.png", renderer);
	resources["bigdot"] = new GameImage("big_dot.png", renderer);
	resources["cherry"] = new GameImage("cherry.png", renderer);
	resources["title"] = new GameImage("title.png", renderer);
	resources["win"] = new GameImage("win.png", renderer);
	resources["gameover"] = new GameImage("gameover.png", renderer);

	// Debugging
	resources["target"] = new GameImage("path_dest.png", renderer);
	resources["target_path"] = new GameImage("path_next.png", renderer);
	resources["target_free"] = new GameImage("tile_free.png", renderer);
	
	// Ghosts
	resources["ghost_dead"] = new GameImage("Ghost_Dead_32.png", renderer);

	resources["ghost_vulnerable"] = new GameImage("ghost_vulnerable.png", renderer);
	resources["ghost_vulnerable_eyes"] = new GameImage("ghost_vulnerable_eyes.png", renderer);
	resources["ghost_vulnerable_feet_a"] = new GameImage("ghost_vulnerable_feet_a.png", renderer);
	resources["ghost_vulnerable_feet_b"] = new GameImage("ghost_vulnerable_feet_b.png", renderer);

	resources["ghost_vulnerable_warning"] = new GameImage("ghost_vulnerable_warning.png", renderer);
	resources["ghost_vulnerable_warning_eyes"] = new GameImage("ghost_vulnerable_warning_eyes.png", renderer);
	resources["ghost_vulnerable_warning_feet_a"] = new GameImage("ghost_vulnerable_warning_feet_a.png", renderer);
	resources["ghost_vulnerable_warning_feet_b"] = new GameImage("ghost_vulnerable_warning_feet_b.png", renderer);

	resources["ghost_eyes_right"] = new GameImage("eyes_right.png", renderer);
	resources["ghost_eyes_left"] = new GameImage("eyes_left.png", renderer);
	resources["ghost_eyes_up"] = new GameImage("eyes_up.png", renderer);
	resources["ghost_eyes_down"] = new GameImage("eyes_down.png", renderer);

	resources["ghost_shadow"] = new GameImage("shadow.png", renderer);
	resources["ghost_shadow_feet_a"] = new GameImage("shadow_feet_a.png", renderer);
	resources["ghost_shadow_feet_b"] = new GameImage("shadow_feet_b.png", renderer);

	resources["ghost_speedy"] = new GameImage("speedy.png", renderer);
	resources["ghost_speedy_feet_a"] = new GameImage("speedy_feet_a.png", renderer);
	resources["ghost_speedy_feet_b"] = new GameImage("speedy_feet_b.png", renderer);

	resources["ghost_bashful"] = new GameImage("bashful.png", renderer);
	resources["ghost_bashful_feet_a"] = new GameImage("bashful_feet_a.png", renderer);
	resources["ghost_bashful_feet_b"] = new GameImage("bashful_feet_b.png", renderer);

	resources["ghost_pokey"] = new GameImage("pokey.png", renderer);
	resources["ghost_pokey_feet_a"] = new GameImage("pokey_feet_a.png", renderer);
	resources["ghost_pokey_feet_b"] = new GameImage("pokey_feet_b.png", renderer);

	// Pacman
	// Open
	resources["pacman_right_open"] = new GameImage("open_right.png", renderer);
	resources["pacman_left_open"] = new GameImage("open_left.png", renderer);
	resources["pacman_up_open"] = new GameImage("open_up.png", renderer);
	resources["pacman_down_open"] = new GameImage("open_down.png", renderer);

	// Closed
	resources["pacman_right_closed"] = new GameImage("closed_right_32.png", renderer);
	resources["pacman_left_closed"] = new GameImage("closed_left_32.png", renderer);
	resources["pacman_up_closed"] = new GameImage("closed_up_32.png", renderer);
	resources["pacman_down_closed"] = new GameImage("closed_down_32.png", renderer);

	// Transition
	resources["pacman_transition_right"] = new GameImage("transition_right.png", renderer);
	resources["pacman_transition_left"] = new GameImage("transition_left.png", renderer);
	resources["pacman_transition_up"] = new GameImage("transition_up.png", renderer);
	resources["pacman_transition_down"] = new GameImage("transition_down.png", renderer);

	// Death animation
	resources["pacman_death_0"] = new GameImage("death_0.png", renderer);
	resources["pacman_death_1"] = new GameImage("death_1.png", renderer);
	resources["pacman_death_2"] = new GameImage("death_2.png", renderer);
	resources["pacman_death_3"] = new GameImage("death_3.png", renderer);
	resources["pacman_death_4"] = new GameImage("death_4.png", renderer);
	resources["pacman_death_5"] = new GameImage("death_5.png", renderer);
	resources["pacman_death_6"] = new GameImage("death_6.png", renderer);
	resources["pacman_death_7"] = new GameImage("death_7.png", renderer);
	resources["pacman_death_8"] = new GameImage("death_8.png", renderer);
	resources["pacman_death_9"] = new GameImage("death_9.png", renderer);
	resources["pacman_death_10"] = new GameImage("death_10.png", renderer);
	resources["pacman_death_11"] = new GameImage("death_11.png", renderer);

	return true;
}

void Drawer::DrawText(const char* text, const char* fontFile, int x, int y, SDL_Color fg)
{
	// If there is no text do not attempt to draw anything
	if (text == "")
		return;

	// Open the font at the font file with a fontsize of 24
	TTF_Font* font=TTF_OpenFont(fontFile, 24);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, fg);

	if (surface == NULL)
		return;

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect sizeRect;
    sizeRect.x = 0 ;
    sizeRect.y = 0 ;
    sizeRect.w = surface->w ;
    sizeRect.h = surface->h ;

    SDL_Rect posRect ;
    posRect.x = x;
    posRect.y = y;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(renderer, optimizedSurface, &sizeRect, &posRect);
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
	SDL_RenderCopy(renderer, resource->optimizedSurface, &resource->sizeRect, &posRect);
}
