#include "Pacman.h"
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

Pacman* Pacman::Create(Drawer* aDrawer)
{
	Pacman* pacman = new Pacman(aDrawer);

	if (!pacman->Init())
	{
		delete pacman;
		pacman = NULL;
	}

	return pacman;
}

Pacman::Pacman(Drawer* aDrawer)
: myDrawer(aDrawer)
, myTimeToNextUpdate(0.f)
, myScore(0)
, myFps(0)
, myLives(3)
, myGhostGhostCounter(0.f)
{
	myAvatar = new Avatar(Vector2f(13*22,22*22));

	ghosts[0] = new GhostShadow(Vector2f(11 * 22, 13 * 22));
	ghosts[1] = new GhostSpeedy(Vector2f(12 * 22, 13 * 22));
	ghosts[2] = new GhostBashful(Vector2f(13 * 22, 13 * 22));
	ghosts[3] = new GhostPokey(Vector2f(14 * 22, 13 * 22));

	myWorld = new World();
}

Pacman::~Pacman(void)
{
}

bool Pacman::Init()
{
	myWorld->Init();

	return true;
}

bool Pacman::Update(float aTime)
{
	if (!UpdateInput())
		return false;

	if (CheckEndGameCondition())
	{
		myDrawer->DrawText("You win!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);
		return true;
	}
	else if (myLives <= 0)
	{
		myDrawer->DrawText("You lose!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);	
		return true;
	}

	MoveAvatar();
	myAvatar->Update(aTime);
	myWorld->Update();
	for (int i = 0; i < GhostCount(); i++) {
		ghosts[i]->Update(aTime, myWorld);
	}

	if (myWorld->HasIntersectedDot(myAvatar->GetPosition()))
		myScore += 10;

	if (myWorld->HasIntersectedCherry(myAvatar->GetPosition())) {
		myScore += 100;
	}

	myGhostGhostCounter -= aTime;

	if (myWorld->HasIntersectedBigDot(myAvatar->GetPosition()))
	{
		myScore += 20;
		myGhostGhostCounter = 20.f;
		for (int i = 0; i < GhostCount(); i++) {
			ghosts[i]->myIsClaimableFlag = true;
		}
	}

	if (myGhostGhostCounter <= 0)
	{
		for (int i = 0; i < GhostCount(); i++) {
			ghosts[i]->myIsClaimableFlag = false;
		}
	}

	for (int i = 0; i < GhostCount(); i++) {
		if ((ghosts[i]->GetPosition() - myAvatar->GetPosition()).Length() < 10.f)
		{
			if (myGhostGhostCounter <= 0.f)
			{
				myLives--;

				myAvatar->SetPosition(Vector2f(13 * 22, 22 * 22));
				ghosts[i]->SetPosition(Vector2f(13 * 22, 13 * 22));
			}
			else if (ghosts[i]->myIsClaimableFlag && !ghosts[i]->myIsDeadFlag)
			{
				myScore += 50;
				ghosts[i]->myIsDeadFlag = true;
				ghosts[i]->Die(myWorld);
			}
		}
	}
	
	if (aTime > 0)
		myFps = (int) (1 / aTime);

	return true;
}

bool Pacman::UpdateInput()
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_UP])
		myAvatar->myNextMovement = myAvatar->move_up;
	else if (keystate[SDL_SCANCODE_DOWN])
		myAvatar->myNextMovement = myAvatar->move_down;
	else if (keystate[SDL_SCANCODE_RIGHT])
		myAvatar->myNextMovement = myAvatar->move_right;
	else if (keystate[SDL_SCANCODE_LEFT])
		myAvatar->myNextMovement = myAvatar->move_left;

	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;

	return true;
}

void Pacman::MoveAvatar()
{
	int nextTileX = myAvatar->GetCurrentTileX() + myAvatar->myNextMovement.myX;
	int nextTileY = myAvatar->GetCurrentTileY() + myAvatar->myNextMovement.myY;

	if (myAvatar->IsAtDestination())
	{
		if (myWorld->TileIsValid(nextTileX, nextTileY))
		{
			myAvatar->SetNextTile(nextTileX, nextTileY);
		}
	}
}

bool Pacman::CheckEndGameCondition()
{
	return myWorld->DotsCount() == 0 && myWorld->BigDotsCount() == 0;
}

bool Pacman::Draw()
{
	myWorld->Draw(myDrawer);
	myAvatar->Draw(myDrawer);
	for (int i = 0; i < GhostCount(); i++) {
		ghosts[i]->Draw(myDrawer);
	}

	std::string scoreString;
	std::stringstream scoreStream;
	scoreStream << myScore;
	scoreString = scoreStream.str();
	myDrawer->DrawText("Score", "font-joystix\\Joystix.ttf", 20, 50);
	myDrawer->DrawText(scoreString.c_str(), "font-joystix\\Joystix.ttf", 120, 50);

	std::string livesString;
	std::stringstream liveStream;
	liveStream << myLives;
	livesString = liveStream.str();
	myDrawer->DrawText("Lives", "font-joystix\\Joystix.ttf", 20, 80);
	myDrawer->DrawText(livesString.c_str(), "font-joystix\\Joystix.ttf", 120, 80);

	myDrawer->DrawText("FPS", "font-joystix\\Joystix.ttf", 880, 50);
	std::string fpsString;
	std::stringstream fpsStream;
	fpsStream << myFps;
	fpsString = fpsStream.str();
	myDrawer->DrawText(fpsString.c_str(), "font-joystix\\Joystix.ttf", 940, 50);

	return true;
}
