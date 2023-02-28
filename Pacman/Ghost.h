#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"

class World;
class Avatar;
class PathmapTile;

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

	virtual void Behaviour(World* aWorld, Avatar* pacman, Ghost* ghosts[4]) {}

	void Draw(Drawer* aDrawer);

protected:

	float speed = 30.f;
	float speedMultiplier = 5.f;
	int myDesiredMovementX;
	int myDesiredMovementY;
	bool nextFrame = false;
	std::string name = "shadow";

	std::list<PathmapTile*> myPath;

private:
	int animation_delta_time = 0;
	int animation_time = 30;
	std::string eyePhase = "right";
};

#endif // GHOST_H