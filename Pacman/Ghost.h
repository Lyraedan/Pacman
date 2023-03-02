#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"
#include "Vector2f.h"
#include "PathmapTile.h"

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
		return myCurrentTileX == nextPathX && myCurrentTileY == nextPathY;
	}

	bool HasReachedRespawnPoint() {
		return myCurrentTileX == spawnX && myCurrentTileY == spawnY;
	}

	void ClearPath() {
		myPath.clear();
	}

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

	int nextPathX = 13;
	int nextPathY = 13;

	int scatterX = 0;
	int scatterY = 0;

	int spawnX = 13;
	int spawnY = 13;

	int scatterTimer = 0;
	int scatterDelay = 15 * 1000;
	bool isScattering = false;

	// Used to move the ghosts to their corners at the start
	bool initialSetup = false;

	// Debugging
	bool showPath = false;
	bool showNextTarget = false;

private:
	int animation_delta_time = 0;
	int animation_time = 30;
	std::string eyePhase = "right";
};

#endif // GHOST_H