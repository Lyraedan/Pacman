#include "Pacman.h"

Pacman* Pacman::Create(Drawer* drawer)
{
	Pacman* pacman = new Pacman(drawer);

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
	score = 0;
	fps = 0;
	lives = 3;

	pacman = new Avatar(Vector2f(13 * 22, 22 * 22));

	ghosts[0] = new GhostShadow(Vector2f(12 * 22, 11 * 22));
	ghosts[1] = new GhostSpeedy(Vector2f(11 * 22, 13 * 22));
	ghosts[2] = new GhostBashful(Vector2f(12 * 22, 13 * 22));
	ghosts[3] = new GhostPokey(Vector2f(13 * 22, 13 * 22));

	world = new World();

	audioPlayer = new AudioPlayer();

	menu = new TitleMenu();
	audioPlayer->PlayWavOnce("sounds/intro.wav", 6, 190.f, 0, false);
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
			audioPlayer->PlayWavOnce("sounds/intro.wav", 6, 190.f, 0, false);
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
		HandleGhosts(delta);
		HandlePickups();
		HandleTeleport();

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
			pacman->myNextMovement = pacman->move_up;
		else if (keystate[SDL_SCANCODE_DOWN])
			pacman->myNextMovement = pacman->move_down;
		else if (keystate[SDL_SCANCODE_RIGHT])
			pacman->myNextMovement = pacman->move_right;
		else if (keystate[SDL_SCANCODE_LEFT])
			pacman->myNextMovement = pacman->move_left;
	}

	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;

	return true;
}

void Pacman::MoveAvatar()
{
	int nextTileX = (int)(pacman->GetCurrentTileX() + pacman->myNextMovement.x);
	int nextTileY = (int)(pacman->GetCurrentTileY() + pacman->myNextMovement.y);

	if (pacman->IsAtDestination())
	{
		if (world->TileIsValid(nextTileX, nextTileY))
		{
			pacman->SetNextTile(nextTileX, nextTileY);
		}
	}
}

void Pacman::HandleGhosts(float delta)
{
	for (int i = 0; i < GhostCount(); i++) {
		if (!pacman->dieAnimation) {
			ghosts[i]->Behaviour(world, pacman, ghosts);
			ghosts[i]->Update(delta, world);
		}

		// If the ghosts touch a teleporter teleport them to the teleporter adjacent
		Teleport* currentGhostTeleport = world->HasIntersectedTeleport(ghosts[i]->GetPosition());
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
				// kill pacman
				audioPlayer->PlayWavOnce("sounds/pacman_death.wav", 1.7f, 220.f, 2, false);

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
}

void Pacman::HandlePickups()
{
	// If pacman touches a dot
	if (world->HasIntersectedDot(pacman->GetPosition())) {
		score += 10;
		audioPlayer->PlayWavOnce("sounds/waka.wav", 0.25f, 5.f, 0, false);
	}

	// If pacman picks up fruit
	if (world->HasIntersectedCherry(pacman->GetPosition())) {
		score += 100;
		audioPlayer->PlayWavOnce("sounds/fruit.wav", 1.f, 5.f, 0, false);
	}

	// If pacman picks up a big dot
	if (world->HasIntersectedBigDot(pacman->GetPosition()))
	{
		score += 20;
		audioPlayer->PlayWavOnce("sounds/ghosts_scared.wav", 6, 190.f, 1, true);
		for (int i = 0; i < GhostCount(); i++) {
			if (!ghosts[i]->isDead) {
				ghosts[i]->ClearPath();
				ghosts[i]->claimableTimer = 0;
				ghosts[i]->isVulnerable = true;
			}
		}
	}
}

void Pacman::HandleTeleport()
{
	// If pacman touches a teleporter teleport him to the adjacent teleporter
	Teleport* currentPlayerTeleport = world->HasIntersectedTeleport(pacman->GetPosition());
	if (currentPlayerTeleport != NULL) {
		if (currentPlayerTeleport->teleportIndex == 0) {
			// Triggers left teleport
			int x = 24;
			int y = pacman->GetCurrentTileY();
			int nextX = x - 1;
			int nextY = pacman->GetCurrentTileY();
			pacman->TeleportTo(x, y, nextX, nextY);
		}
		else {
			// Triggers right teleport
			int x = 1;
			int y = pacman->GetCurrentTileY();
			int nextX = x + 1;
			int nextY = pacman->GetCurrentTileY();
			pacman->TeleportTo(x, y, nextX, nextY);
		}
	}
}

bool Pacman::Draw()
{
	if (menu != NULL) {
		menu->Draw(drawer);
	}
	else {
		world->Draw(drawer);
		pacman->Draw(drawer);

		// If pacman is performing the dying animation do not draw the ghosts
		if (!pacman->dieAnimation) {
			for (int i = 0; i < GhostCount(); i++) {
				ghosts[i]->Draw(drawer);
			}
		}

		// Draw the ready text
		if (readyTime <= readyDelay) {
			drawer->DrawText("Ready!", "font-joystix\\Joystix.ttf", 470, 280, { 255, 255, 0, 255 });
		}

		// Draw the score
		int scoreX = 220;
		int scoreY = 10;
		std::string scoreString;
		std::stringstream scoreStream;
		scoreStream << score;
		scoreString = scoreStream.str();
		drawer->DrawText(("Score " + scoreString).c_str(), "font-joystix\\Joystix.ttf", scoreX + 100, scoreY, { 255, 255, 255, 255 });

		// Draw the lives
		int livesX = 700 - (32 * lives);
		int livesY = 10;
		for (int i = 0; i < lives; i++) {
			drawer->DrawResource(drawer->resources["pacman_transition_left"], livesX + 90 + (i * 32), livesY - 5);
		}

		// Draw the fps count
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
