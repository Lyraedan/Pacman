#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"

Ghost::Ghost(const Vector2f& position) : MovableGameEntity(position)
{
	activeResourceKey = "";

	isVulnerable = false;
	isDead = false;
}

Ghost::~Ghost(void)
{
}

void Ghost::Die(World* world)
{
	ClearPath();
	nextTile = respawn;
	world->GetPath(currentTile, nextTile, currentPath);
}

void Ghost::Update(float delta, World* world)
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

	bool followingPath = FollowPath(delta);
	if (!followingPath)
	{
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
	Vector2f destination = Vector2f(nextTile.x * tileSize, nextTile.y * tileSize);
	Vector2f ghostPosition = GetPosition();
	Vector2f direction = destination - ghostPosition;

	float distanceToMove = delta * speed * speedMultiplier;

	if (distanceToMove > direction.Length())
	{
		SetPosition(destination);
		currentTile = nextTile;
	}
	else
	{
		direction.Normalize();
		UpdateEyes(direction);
		UpdatePosition(direction * distanceToMove);
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

void Ghost::Draw(Drawer* drawer)
{
	Vector2f position = GetPosition();

	std::string foot = nextFrame ? "b" : "a";
	int offsetX = 220;
	int offsetY = 60;

	bool warning = claimableTimer >= (claimableLength / 2) && (claimableTimer % 100 >= 50);
	std::string warningState = warning ? "_warning" : "";

	int x = (int) position.x + offsetX;
	int y = (int) position.y + offsetY;

	if (isDead) {
		drawer->DrawResource(drawer->resources["ghost_eyes_" + eyePhase], x, y);
	}
	else if (isVulnerable) {
		drawer->DrawResource(drawer->resources["ghost_vulnerable" + warningState], x, y);
		drawer->DrawResource(drawer->resources["ghost_vulnerable" + warningState + "_feet_" + foot], x, y);
		drawer->DrawResource(drawer->resources["ghost_vulnerable" + warningState + "_eyes"], x, y);
	}
	else {
		drawer->DrawResource(drawer->resources[activeResourceKey], x, y);
		drawer->DrawResource(drawer->resources["ghost_" + name + "_feet_" + foot], x, y);
		drawer->DrawResource(drawer->resources["ghost_eyes_" + eyePhase], x, y);
	}

	// debugging
	if (showPath) {
		for (PathmapTile* tile : currentPath) {
			Vector2f tilePosition = tile->GetPosition();
			drawer->DrawResource(drawer->resources["target_path"], 220 + tilePosition.x * 22, 66 + tilePosition.y * 22);
		}
	}

	if (showNextTarget) {
		drawer->DrawResource(drawer->resources["target"], 220 + nextTile.x * 22, 88 + nextTile.y * 22);
	}
}

bool Ghost::FollowPath(float delta)
{
	if (currentPath.empty())
		return false;

	Vector2f next = currentPath.front()->GetPosition();
	nextTile = next;
	bool atNext = currentTile == nextTile;
	if (atNext) {
		currentPath.pop_front();
		return true;
	}
	return false;
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
