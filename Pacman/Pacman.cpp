#include "Pacman.h"

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
{
	myAvatar = new Avatar(Vector2f(13 * 22, 22 * 22));

	ghosts[0] = new GhostShadow(Vector2f(12 * 22, 11 * 22));
	ghosts[1] = new GhostSpeedy(Vector2f(11 * 22, 13 * 22));
	ghosts[2] = new GhostBashful(Vector2f(12 * 22, 13 * 22));
	ghosts[3] = new GhostPokey(Vector2f(13 * 22, 13 * 22));

	myWorld = new World();

	audioPlayer = new AudioPlayer();

	menu = new TitleMenu();
	audioPlayer->PlayWavOnce("intro.wav", 6, 190.f, 0, false);
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

	if (menu != NULL) {
		menu->Update(aTime);
	} 
	else {
		if (readyTime <= readyDelay) {
			readyTime++;
			audioPlayer->PlayWavOnce("intro.wav", 6, 190.f, 0, false);
			return true;
		}

		if (CheckEndGameCondition())
		{
			menu = new WinMenu(myScore);
			audioPlayer->Stop();
			return true;
		}
		else if (myLives <= 0)
		{
			menu = new LoseMenu(myScore);
			audioPlayer->Stop();
			return true;
		}

		MoveAvatar();
		myAvatar->Update(aTime);
		myWorld->Update();

		for (int i = 0; i < GhostCount(); i++) {
			if (!myAvatar->dieAnimation) {
				ghosts[i]->Behaviour(myWorld, myAvatar, ghosts);
				ghosts[i]->Update(aTime, myWorld);
			}

			// If the ghosts touch a teleporter teleport them to the teleporter adjacent
			Teleport* currentGhostTeleport = myWorld->HasIntersectedTeleport(ghosts[i]->GetPosition());
			if (currentGhostTeleport != NULL) {
				if (currentGhostTeleport->teleportIndex == 0) {
					int x = 24;
					int y = ghosts[i]->GetCurrentTileY();
					int nextX = x - 1;
					int nextY = ghosts[i]->GetCurrentTileY();
					ghosts[i]->TeleportTo(x, y, nextX, nextY);
				}
				else {
					int x = 1;
					int y = ghosts[i]->GetCurrentTileY();
					int nextX = x + 1;
					int nextY = ghosts[i]->GetCurrentTileY();
					ghosts[i]->TeleportTo(x, y, nextX, nextY);
				}
			}

			// Stop the ghost scared sfx as the claimable phase ends
			if (ghosts[i]->claimableTimer >= ghosts[i]->claimableLength - 1) {
				audioPlayer->Stop();
			}

			// If the ghosts touch pacman
			if (myWorld->HasIntersectedPacman(ghosts[i], myAvatar)) {
				if (ghosts[i]->myIsClaimableFlag) {
					if (!ghosts[i]->myIsDeadFlag) {
						// Kill the ghosts
						myScore += 50;
						ghosts[i]->myIsDeadFlag = true;
						ghosts[i]->Die(myWorld);
					}
				}
				else {
					// attack pacman
					audioPlayer->PlayWavOnce("pacman_death.wav", 1.7f, 220.f, 2, false);

					myAvatar->Die([=]() {
						myLives--;
						myAvatar->TeleportTo(13, 22, 13, 22);
						for (int j = 0; j < GhostCount(); j++) {
							ghosts[j]->ClearPath();
							ghosts[j]->TeleportTo(10 + (j + 1), 13, 11, 13);
							// Reset
							ghosts[j]->speed = 30.f;
							ghosts[j]->claimableTimer = 0;
							ghosts[j]->myIsClaimableFlag = false;
							ghosts[j]->myIsDeadFlag = false;
						}
						audioPlayer->SetCurrentPriority(0);
					});
				}
			}
		}

		// If pacman touches a dot
		if (myWorld->HasIntersectedDot(myAvatar->GetPosition())) {
			myScore += 10;
			audioPlayer->PlayWavOnce("waka.wav", 0.25f, 5.f, 0, false);
		}

		// If pacman picks up fruit
		if (myWorld->HasIntersectedCherry(myAvatar->GetPosition())) {
			myScore += 100;
			audioPlayer->PlayWavOnce("fruit.wav", 1.f, 5.f, 0, false);
		}

		// If pacman touches a teleporter teleport him to the adjacent teleporter
		Teleport* currentPlayerTeleport = myWorld->HasIntersectedTeleport(myAvatar->GetPosition());
		if (currentPlayerTeleport != NULL) {
			if (currentPlayerTeleport->teleportIndex == 0) {
				// Triggers left teleport
				int x = 24;
				int y = myAvatar->GetCurrentTileY();
				int nextX = x - 1;
				int nextY = myAvatar->GetCurrentTileY();
				myAvatar->TeleportTo(x, y, nextX, nextY);
			}
			else {
				// Triggers right teleport
				int x = 1;
				int y = myAvatar->GetCurrentTileY();
				int nextX = x + 1;
				int nextY = myAvatar->GetCurrentTileY();
				myAvatar->TeleportTo(x, y, nextX, nextY);
			}
		}

		// If pacman picks up a big dot
		if (myWorld->HasIntersectedBigDot(myAvatar->GetPosition()))
		{
			myScore += 20;
			audioPlayer->PlayWavOnce("ghosts_scared.wav", 6, 190.f, 1, true);
			for (int i = 0; i < GhostCount(); i++) {
				if (!ghosts[i]->myIsDeadFlag) {
					ghosts[i]->ClearPath();
					ghosts[i]->claimableTimer = 0;
					ghosts[i]->myIsClaimableFlag = true;
				}
			}
		}

		if (aTime > 0)
			myFps = (int)(1 / aTime);
	}
	return true;
}

bool Pacman::UpdateInput()
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	if (menu != NULL) {
		if (keystate[SDL_SCANCODE_SPACE]) {
			audioPlayer->Stop();
			menu = NULL;
		}
	}
	else {
		if (keystate[SDL_SCANCODE_UP])
			myAvatar->myNextMovement = myAvatar->move_up;
		else if (keystate[SDL_SCANCODE_DOWN])
			myAvatar->myNextMovement = myAvatar->move_down;
		else if (keystate[SDL_SCANCODE_RIGHT])
			myAvatar->myNextMovement = myAvatar->move_right;
		else if (keystate[SDL_SCANCODE_LEFT])
			myAvatar->myNextMovement = myAvatar->move_left;
	}

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
	if (menu != NULL) {
		menu->Draw(myDrawer);
	}
	else {
		myWorld->Draw(myDrawer);
		myAvatar->Draw(myDrawer);

		if (!myAvatar->dieAnimation) {
			for (int i = 0; i < GhostCount(); i++) {
				ghosts[i]->Draw(myDrawer);
			}
		}

		if (readyTime <= readyDelay) {
			myDrawer->DrawText("Ready!", "font-joystix\\Joystix.ttf", 470, 280, { 255, 255, 0, 255 });
		}

		int scoreX = 220;
		int scoreY = 10;
		std::string scoreString;
		std::stringstream scoreStream;
		scoreStream << myScore;
		scoreString = scoreStream.str();
		myDrawer->DrawText(("Score " + scoreString).c_str(), "font-joystix\\Joystix.ttf", scoreX + 100, scoreY, { 255, 255, 255, 255 });

		int livesX = 700 - (32 * myLives);
		int livesY = 10;
		for (int i = 0; i < myLives; i++) {
			myDrawer->DrawResource(myDrawer->resources["pacman_transition_left"], livesX + 90 + (i * 32), livesY - 5);
		}

		int fpsX = 460;
		int fpsY = 10;
		std::string fpsString;
		std::stringstream fpsStream;
		fpsStream << myFps;
		fpsString = fpsStream.str();
		myDrawer->DrawText(("FPS " + fpsString).c_str(), "font-joystix\\Joystix.ttf", fpsX + 60, fpsY, { 255, 255, 255, 255 });
	}
	return true;
}
