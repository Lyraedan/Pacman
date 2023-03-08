#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"

Ghost::Ghost(const Vector2f& aPosition)
: MovableGameEntity(aPosition)
{
	activeResourceKey = "";

	isVulnerable = false;
	isDead = false;
}

Ghost::~Ghost(void)
{
}

void Ghost::Die(World* aWorld)
{
	ClearPath();
	nextTile = Vector2f(spawnX, spawnY);
	aWorld->GetPath(currentTileX, currentTileY, nextTile.x, nextTile.y, myPath);
}

void Ghost::Update(float aTime, World* aWorld)
{
	if (isDead)
		speed = 120.f;

	if (isVulnerable) {
		claimableTimer++;
		if (claimableTimer >= claimableLength) {
			claimableTimer = 0;
			if(!isDead)
				isVulnerable = false;
		}
	}

	animation_delta_time++;
	if (animation_delta_time >= animation_time) {
		nextFrame = !nextFrame;
		animation_delta_time = 0;
	}

	scatterTimer++;
	if (scatterTimer >= scatterDelay) {
		isScattering = !isScattering;
		scatterDelay = isScattering ? 3 * 1000 : 15 * 1000;
		scatterTimer = 0;
	}

	path_update_time++;
	if (path_update_time >= path_update_interval) {
		if(!isDead)
			ClearPath();
		path_update_time = 0;
	}

	if (IsAtDestination())
	{
		if (!myPath.empty())
		{
			PathmapTile* nextTile = myPath.front();
			myPath.pop_front();
			SetNextTile(nextTile->x, nextTile->y);
		}

		if (HasReachedEndOfPath()) {
			if (!initialSetup)
				initialSetup = true;
			ClearPath();
		}

		if (HasReachedRespawnPoint() && isDead) {
			isVulnerable = false;
			isDead = false;
			speed = 30.f;
		}
	}

	// Move the ghosts
	int tileSize = 22;
	Vector2f destination(nextTileX * tileSize, nextTileY * tileSize);
	Vector2f direction = destination - position;

	float distanceToMove = aTime * speed * speedMultiplier;

	if (distanceToMove > direction.Length())
	{
		position = destination;
		currentTileX = nextTileX;
		currentTileY = nextTileY;
	}
	else
	{
		direction.Normalize();
		UpdateEyes(direction);
		position += direction * distanceToMove;
	}
}

void Ghost::UpdateEyes(Vector2f direction)
{
	if (direction.x == 1)
		eyePhase = "right";
	else if (direction.y == 1)
		eyePhase = "down";
	else if (direction.x == -1)
		eyePhase = "left";
	else if(direction.y == -1)
		eyePhase = "up";

}

void Ghost::SetResource(const char* resourceKey)
{
	this->activeResourceKey = resourceKey;
}

void Ghost::Draw(Drawer* aDrawer)
{
	std::string foot = nextFrame ? "b" : "a";
	int offsetX = 220;
	int offsetY = 60;

	bool warning = claimableTimer >= (claimableLength / 2) && (claimableTimer % 100 >= 50);
	std::string warningState = warning ? "_warning" : "";

	if (isDead) {
		aDrawer->DrawResource(aDrawer->resources["ghost_eyes_" + eyePhase], (int)position.x + offsetX, (int)position.y + offsetY);
	}
	else if (isVulnerable) {
		aDrawer->DrawResource(aDrawer->resources["ghost_vulnerable" + warningState], (int)position.x + offsetX, (int)position.y + offsetY);
		aDrawer->DrawResource(aDrawer->resources["ghost_vulnerable" + warningState + "_feet_" + foot], (int)position.x + offsetX, (int)position.y + offsetY);
		aDrawer->DrawResource(aDrawer->resources["ghost_vulnerable" + warningState + "_eyes"], (int)position.x + offsetX, (int)position.y + offsetY);
	}
	else {
		aDrawer->DrawResource(aDrawer->resources[activeResourceKey], (int)position.x + offsetX, (int)position.y + offsetY);
		aDrawer->DrawResource(aDrawer->resources["ghost_" + name + "_feet_" + foot], (int)position.x + offsetX, (int)position.y + offsetY);
		aDrawer->DrawResource(aDrawer->resources["ghost_eyes_" + eyePhase], (int)position.x + offsetX, (int)position.y + offsetY);
	}

	// debugging
	if (showPath) {
		for (PathmapTile* tile : myPath) {
			aDrawer->DrawResource(aDrawer->resources["target_path"], 220 + tile->x * 22, 66 + tile->y * 22);
		}
	}

	if (showNextTarget) {
		aDrawer->DrawResource(aDrawer->resources["target"], 220 + nextTile.x * 22, 88 + nextTile.y * 22);
	}
}

Vector2f Ghost::OffsetFromPacman(Avatar* pacman, int offset)
{
	int changeX = 0;
	int changeY = 0;

	if (pacman->direction.x == 1)
		changeX = offset;
	else if (pacman->direction.y == 1)
		changeY = offset;
	else if (pacman->direction.x == -1)
		changeX = -offset;
	else if (pacman->direction.y == -1)
		changeY = -offset;

	return Vector2f(changeX, changeY);
}
