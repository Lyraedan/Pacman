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
	Ghost(const Vector2f& aPosition);
	~Ghost(void);

	void Update(float aTime, World* aWorld);

	bool myIsClaimableFlag;
	bool myIsDeadFlag;

	void SetResource(const char* resourceKey);

	void Die(World* aWorld);

	void UpdateEyes(Vector2f direction);

	virtual void Behaviour(World* aWorld, Avatar* pacman, Ghost* ghosts[4]) {}

	void Draw(Drawer* aDrawer);

	bool HasReachedEndOfPath() {
		return myCurrentTileX == nextTile.myX && myCurrentTileY == nextTile.myY;
	}

	bool HasReachedRespawnPoint() {
		return myCurrentTileX == spawnX && myCurrentTileY == spawnY;
	}

	void ClearPath() {
		myPath.clear();
	}

	Vector2f OffsetFromPacman(Avatar* pacman, int offset);

	int claimableTimer = 0;
	int claimableLength = 1000;
	int respawnX = 13;
	int respawnY = 13;
	float speed = 30.f;

protected:

	float speedMultiplier = 5.f;
	int myDesiredMovementX;
	int myDesiredMovementY;
	bool nextFrame = false;
	std::string name = "shadow";

	std::list<PathmapTile*> myPath;

	Vector2f nextTile = Vector2f(13, 13);
	int currentScatterIndex = 0;

	int spawnX = 13;
	int spawnY = 13;

	int scatterTimer = 0;
	int scatterDelay = 30 * 1000;
	bool isScattering = false;
	Vector2f scatterPoints[4];

	// Used to move the ghosts to their corners at the start
	bool initialSetup = false;

	// Debugging
	bool showPath = false;
	bool showNextTarget = false;

private:
	int animation_delta_time = 0;
	int animation_time = 30;
	std::string eyePhase = "right";

	int path_update_time = 0;
	int path_update_interval = 1000;
};

#endif // GHOST_H