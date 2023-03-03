#ifndef PACMAN_H
#define PACMAN_H

#include "Vector2f.h"
#include "Drawer.h"
#include "SDL.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Avatar.h"
#include "World.h"

#include "GhostShadow.h"
#include "GhostSpeedy.h"
#include "GhostBashful.h"
#include "GhostPokey.h"

#include "Teleport.h"
#include "Menu.h"

#include "TitleMenu.h"
#include "LoseMenu.h"
#include "WinMenu.h"

#include "AudioPlayer.h"

struct SDL_Surface;
class Drawer;
class Avatar;
class World;
class Ghost;
class TitleMenu;
class WinMenu;
class LoseMenu;
class Menu;

class Pacman
{
public:
	static Pacman* Create(Drawer* aDrawer);
	~Pacman(void);

	bool Update(float aTime);
	bool Draw();

private:
	Pacman(Drawer* aDrawer);
	bool Init();
	bool UpdateInput();
	void MoveAvatar();
	bool CheckEndGameCondition();

	int GhostCount() {
		return sizeof(ghosts) / sizeof(int);
	}

	Drawer* myDrawer;

	float myTimeToNextUpdate;

	int myLives;
	int myScore;
	int myFps;

	Avatar* myAvatar;
	Ghost* ghosts[4];
	World* myWorld;

	AudioPlayer* audioPlayer;
	Menu* menu;

	int readyTime = 0;
	int readyDelay = 6 * 190;
};

#endif // PACMAN_H