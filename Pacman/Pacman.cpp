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

Pacman::Pacman(Drawer* drawer)
{
	this->drawer = drawer;
	nextUpdateDelta = 0.f;
	score = 0;
	fps = 0;
	lives = 3;

	pacman = new Avatar(Vector2f(13, 22));

	ghosts[0] = new GhostShadow(Vector2f(12, 11));
	ghosts[1] = new GhostSpeedy(Vector2f(11, 13));
	ghosts[2] = new GhostBashful(Vector2f(12, 13));
	ghosts[3] = new GhostPokey(Vector2f(13, 13));

	world = new World();

	audioPlayer = new AudioPlayer();

	menu = new TitleMenu();
	audioPlayer->PlayWavOnce("intro.wav", 6, 190.f, 0, false);
}

Pacman::~Pacman(void)
{
}

bool Pacman::Init()
{
	world->Init();

	return true;
}

bool Pacman::Update(float delta)
{
	if (!UpdateInput())
		return false;

	if (menu != NULL) {
		menu->Update(delta);
	} 
	else {
		if (readyTime <= readyDelay) {
			readyTime++;
			audioPlayer->PlayWavOnce("intro.wav", 6, 190.f, 0, false);
			return true;
		}

		if (HasWon())
		{
			menu = new WinMenu(score);
			audioPlayer->Stop();
			return true;
		}
		else if (lives <= 0)
		{
			menu = new LoseMenu(score);
			audioPlayer->Stop();
			return true;
		}

		MoveAvatar();
		pacman->Update(delta);
		world->Update();

		ghosts[0]->Behaviour(world, pacman, ghosts);
		ghosts[0]->Update(delta, world);

		for (int i = 0; i < GhostCount(); i++) {
			if (!pacman->dieAnimation) {
				//ghosts[i]->Behaviour(world, pacman, ghosts);
				//ghosts[i]->Update(delta, world);
			}

			// If the ghosts touch a teleporter teleport them to the teleporter adjacent
			Teleport* currentGhostTeleport = world->HasIntersectedTeleport(ghosts[i]->GetPosition());
			if (currentGhostTeleport != NULL) {
				Vector2f positionAsGrid = ghosts[i]->GetPositionAsGridCoordinates();
				if (currentGhostTeleport->teleportIndex == 0) {
					int x = 24;
					int y = positionAsGrid.y;
					int nextX = x - 1;
					int nextY = positionAsGrid.y;
					ghosts[i]->TeleportTo(x, y, nextX, nextY);
				}
				else {
					int x = 1;
					int y = positionAsGrid.y;
					int nextX = x + 1;
					int nextY = positionAsGrid.y;
					ghosts[i]->TeleportTo(x, y, nextX, nextY);
				}
			}

			// Stop the ghost scared sfx as the claimable phase ends
			if (ghosts[i]->claimableTimer >= ghosts[i]->claimableLength - 1) {
				audioPlayer->Stop();
			}

			// If the ghosts touch pacman
			if (world->HasIntersectedPacman(ghosts[i], pacman)) {
				if (ghosts[i]->isVulnerable) {
					if (!ghosts[i]->isDead) {
						// Kill the ghosts
						score += 50;
						ghosts[i]->isDead = true;
						ghosts[i]->Die(world);
					}
				}
				else {
					// attack pacman
					audioPlayer->PlayWavOnce("pacman_death.wav", 1.7f, 220.f, 2, false);

					pacman->Die([=]() {
						lives--;
						pacman->TeleportTo(13, 22, 13, 22);
						for (int j = 0; j < GhostCount(); j++) {
							ghosts[j]->ClearPath();
							ghosts[j]->TeleportTo(10 + (j + 1), 13, 11, 13);
							// Reset
							ghosts[j]->speed = 30.f;
							ghosts[j]->claimableTimer = 0;
							ghosts[j]->isVulnerable = false;
							ghosts[j]->isDead = false;
						}
						audioPlayer->SetCurrentPriority(0);
					});
				}
			}
		}

		// If pacman touches a dot
		if (world->HasIntersectedDot(pacman->GetPosition())) {
			score += 10;
			audioPlayer->PlayWavOnce("waka.wav", 0.25f, 5.f, 0, false);
		}

		// If pacman picks up fruit
		if (world->HasIntersectedCherry(pacman->GetPosition())) {
			score += 100;
			audioPlayer->PlayWavOnce("fruit.wav", 1.f, 5.f, 0, false);
		}

		// If pacman touches a teleporter teleport him to the adjacent teleporter
		Teleport* currentPlayerTeleport = world->HasIntersectedTeleport(pacman->GetPosition());
		if (currentPlayerTeleport != NULL) {
			Vector2f positionAsGrid = pacman->GetPositionAsGridCoordinates();
			if (currentPlayerTeleport->teleportIndex == 0) {
				// Triggers left teleport
				int x = 24;
				int y = positionAsGrid.y;
				int nextX = x - 1;
				int nextY = positionAsGrid.y;
				pacman->TeleportTo(x, y, nextX, nextY);
			}
			else {
				// Triggers right teleport
				int x = 1;
				int y = positionAsGrid.y;
				int nextX = x + 1;
				int nextY = positionAsGrid.y;
				pacman->TeleportTo(x, y, nextX, nextY);
			}
		}

		// If pacman picks up a big dot
		if (world->HasIntersectedBigDot(pacman->GetPosition()))
		{
			score += 20;
			audioPlayer->PlayWavOnce("ghosts_scared.wav", 6, 190.f, 1, true);
			for (int i = 0; i < GhostCount(); i++) {
				if (!ghosts[i]->isDead) {
					ghosts[i]->ClearPath();
					ghosts[i]->claimableTimer = 0;
					ghosts[i]->isVulnerable = true;
				}
			}
		}

		if (delta > 0)
			fps = (int)(1 / delta);
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
			pacman->nextMovement = pacman->move_up;
		else if (keystate[SDL_SCANCODE_DOWN])
			pacman->nextMovement = pacman->move_down;
		else if (keystate[SDL_SCANCODE_RIGHT])
			pacman->nextMovement = pacman->move_right;
		else if (keystate[SDL_SCANCODE_LEFT])
			pacman->nextMovement = pacman->move_left;
	}

	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;

	return true;
}

void Pacman::MoveAvatar()
{
	Vector2f positionOnGrid = pacman->GetPositionAsGridCoordinates();
	Vector2f next = positionOnGrid + pacman->nextMovement;

	if (pacman->IsAtDestination())
	{
		if (world->TileIsValid(next))
		{
			pacman->SetNextTile(next.x, next.y);
		}
	}
}

bool Pacman::HasWon()
{
	return world->DotsCount() == 0 && world->BigDotsCount() == 0;
}

bool Pacman::Draw()
{
	if (menu != NULL) {
		menu->Draw(drawer);
	}
	else {
		world->Draw(drawer);
		pacman->Draw(drawer);

		// Only draw the ghosts if pacman isn't in the dying animation
		if (!pacman->dieAnimation) {
			for (int i = 0; i < GhostCount(); i++) {
				ghosts[i]->Draw(drawer);
			}
		}

		// Draw the "Ready!" text
		if (readyTime <= readyDelay) {
			drawer->DrawText("Ready!", "font-joystix\\Joystix.ttf", 470, 280, { 255, 255, 0, 255 });
		}

		// Todo clean these up
		int scoreX = 220;
		int scoreY = 10;
		std::string scoreString;
		std::stringstream scoreStream;
		scoreStream << score;
		scoreString = scoreStream.str();
		drawer->DrawText(("Score " + scoreString).c_str(), "font-joystix\\Joystix.ttf", scoreX + 100, scoreY, { 255, 255, 255, 255 });

		int livesX = 700 - (32 * lives);
		int livesY = 10;
		for (int i = 0; i < lives; i++) {
			drawer->DrawResource(drawer->resources["pacman_transition_left"], livesX + 90 + (i * 32), livesY - 5);
		}

		int fpsX = 460;
		int fpsY = 10;
		std::string fpsString;
		std::stringstream fpsStream;
		fpsStream << fps;
		fpsString = fpsStream.str();
		drawer->DrawText(("FPS " + fpsString).c_str(), "font-joystix\\Joystix.ttf", fpsX + 60, fpsY, { 255, 255, 255, 255 });
	}
	return true;
}
