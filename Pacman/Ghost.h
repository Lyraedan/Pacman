#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"
#include "Vector2f.h"
#include "PathmapTile.h"
#include "Avatar.h"

class World;
class Avatar;
class PathmapTile;
class Vector2f;

class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f& position);
	~Ghost(void);

	void Update(float delta, World* world);

	bool isVulnerable = false;
	bool isDead = false;

	void SetResource(const char* resourceKey);

	void Die(World* world);

	void UpdateEyes(Vector2f direction);

	virtual void Behaviour(World* world, Avatar* pacman, Ghost* ghosts[4]) {}

	void Draw(Drawer* drawer);

	bool FollowPath(float delta);

	bool HasReachedEndOfPath() {
		if (currentPath.empty())
			return true;

		PathmapTile* last = currentPath.back();
		Vector2f lastPosition = last->GetPosition();
		return currentTile == lastPosition;
	}

	bool HasReachedRespawnPoint() {
		return currentTile == respawn;
	}

	PathmapTile* GetPathTile(int index) {

	}

	void ClearPath() {
		currentPath.clear();
	}

	Vector2f OffsetFromPacman(Avatar* pacman, int offset);

	int claimableTimer = 0;
	int claimableLength = 3000;
	Vector2f respawn = Vector2f(13, 13);
	float speed = 30.f;

protected:

	float speedMultiplier = 5.f;
	bool nextFrame = false;
	std::string name = "shadow";

	std::list<PathmapTile*> currentPath;

	Vector2f nextTile = Vector2f(13, 13);
	int currentScatterIndex = 0;

	Vector2f spawn = Vector2f(13, 13);

	int scatterTimer = 0;
	int scatterDelay = 15 * 1000;
	bool isScattering = false;
	Vector2f scatterPoints[4];

	// Used to move the ghosts to their corners at the start
	bool initialSetup = false;

	// Debugging
	bool showPath = true;
	bool showNextTarget = false;

private:
	int animation_delta_time = 0;
	int animation_time = 30;
	std::string eyePhase = "right";

	int path_update_time = 0;
	int path_update_interval = 1000;
};

#endif // GHOST_H