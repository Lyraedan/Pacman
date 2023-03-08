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
	if (!window)
		return false;

	// Misc
	resources["map"] = new GameImage("world/playfield.png", renderer);
	resources["dot"] = new GameImage("world/small_dot.png", renderer);
	resources["bigdot"] = new GameImage("world/big_dot.png", renderer);
	resources["cherry"] = new GameImage("world/cherry.png", renderer);

	// Menu
	resources["title"] = new GameImage("menu/title.png", renderer);
	resources["win"] = new GameImage("menu/win.png", renderer);
	resources["gameover"] = new GameImage("menu/gameover.png", renderer);

	// Debugging
	resources["target"] = new GameImage("debugging/path_dest.png", renderer);
	resources["target_path"] = new GameImage("debugging/path_next.png", renderer);

	// Ghosts
	resources["ghost_vulnerable"] = new GameImage("ghosts/ghost_vulnerable.png", renderer);
	resources["ghost_vulnerable_eyes"] = new GameImage("ghosts/ghost_vulnerable_eyes.png", renderer);
	resources["ghost_vulnerable_feet_a"] = new GameImage("ghosts/ghost_vulnerable_feet_a.png", renderer);
	resources["ghost_vulnerable_feet_b"] = new GameImage("ghosts/ghost_vulnerable_feet_b.png", renderer);

	resources["ghost_vulnerable_warning"] = new GameImage("ghosts/ghost_vulnerable_warning.png", renderer);
	resources["ghost_vulnerable_warning_eyes"] = new GameImage("ghosts/ghost_vulnerable_warning_eyes.png", renderer);
	resources["ghost_vulnerable_warning_feet_a"] = new GameImage("ghosts/ghost_vulnerable_warning_feet_a.png", renderer);
	resources["ghost_vulnerable_warning_feet_b"] = new GameImage("ghosts/ghost_vulnerable_warning_feet_b.png", renderer);

	resources["ghost_eyes_right"] = new GameImage("ghosts/eyes_right.png", renderer);
	resources["ghost_eyes_left"] = new GameImage("ghosts/eyes_left.png", renderer);
	resources["ghost_eyes_up"] = new GameImage("ghosts/eyes_up.png", renderer);
	resources["ghost_eyes_down"] = new GameImage("ghosts/eyes_down.png", renderer);

	resources["ghost_shadow"] = new GameImage("ghosts/shadow.png", renderer);
	resources["ghost_shadow_feet_a"] = new GameImage("ghosts/shadow_feet_a.png", renderer);
	resources["ghost_shadow_feet_b"] = new GameImage("ghosts/shadow_feet_b.png", renderer);

	resources["ghost_speedy"] = new GameImage("ghosts/speedy.png", renderer);
	resources["ghost_speedy_feet_a"] = new GameImage("ghosts/speedy_feet_a.png", renderer);
	resources["ghost_speedy_feet_b"] = new GameImage("ghosts/speedy_feet_b.png", renderer);

	resources["ghost_bashful"] = new GameImage("ghosts/bashful.png", renderer);
	resources["ghost_bashful_feet_a"] = new GameImage("ghosts/bashful_feet_a.png", renderer);
	resources["ghost_bashful_feet_b"] = new GameImage("ghosts/bashful_feet_b.png", renderer);

	resources["ghost_pokey"] = new GameImage("ghosts/pokey.png", renderer);
	resources["ghost_pokey_feet_a"] = new GameImage("ghosts/pokey_feet_a.png", renderer);
	resources["ghost_pokey_feet_b"] = new GameImage("ghosts/pokey_feet_b.png", renderer);

	// Pacman
	// Open
	resources["pacman_right_open"] = new GameImage("pacman/open_right.png", renderer);
	resources["pacman_left_open"] = new GameImage("pacman/open_left.png", renderer);
	resources["pacman_up_open"] = new GameImage("pacman/open_up.png", renderer);
	resources["pacman_down_open"] = new GameImage("pacman/open_down.png", renderer);

	// Closed
	resources["pacman_right_closed"] = new GameImage("pacman/closed_right.png", renderer);
	resources["pacman_left_closed"] = new GameImage("pacman/closed_left.png", renderer);
	resources["pacman_up_closed"] = new GameImage("pacman/closed_up.png", renderer);
	resources["pacman_down_closed"] = new GameImage("pacman/closed_down.png", renderer);

	// Transition
	resources["pacman_transition_right"] = new GameImage("pacman/transition_right.png", renderer);
	resources["pacman_transition_left"] = new GameImage("pacman/transition_left.png", renderer);
	resources["pacman_transition_up"] = new GameImage("pacman/transition_up.png", renderer);
	resources["pacman_transition_down"] = new GameImage("pacman/transition_down.png", renderer);

	// Death animation
	resources["pacman_death_0"] = new GameImage("pacman/death_0.png", renderer);
	resources["pacman_death_1"] = new GameImage("pacman/death_1.png", renderer);
	resources["pacman_death_2"] = new GameImage("pacman/death_2.png", renderer);
	resources["pacman_death_3"] = new GameImage("pacman/death_3.png", renderer);
	resources["pacman_death_4"] = new GameImage("pacman/death_4.png", renderer);
	resources["pacman_death_5"] = new GameImage("pacman/death_5.png", renderer);
	resources["pacman_death_6"] = new GameImage("pacman/death_6.png", renderer);
	resources["pacman_death_7"] = new GameImage("pacman/death_7.png", renderer);
	resources["pacman_death_8"] = new GameImage("pacman/death_8.png", renderer);
	resources["pacman_death_9"] = new GameImage("pacman/death_9.png", renderer);
	resources["pacman_death_10"] = new GameImage("pacman/death_10.png", renderer);
	resources["pacman_death_11"] = new GameImage("pacman/death_11.png", renderer);


	return true;
}

void Drawer::DrawText(const char* text, const char* fontFile, int x, int y, SDL_Color fg)
{
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
