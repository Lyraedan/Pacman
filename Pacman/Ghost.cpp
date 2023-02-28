#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"

Ghost::Ghost(const Vector2f& aPosition)
: MovableGameEntity(aPosition)
{
	activeResourceKey = "ghost_test";

	myIsClaimableFlag = false;
	myIsDeadFlag = false;

	myDesiredMovementX = 0;
	myDesiredMovementY = -1;
}

Ghost::~Ghost(void)
{
}

void Ghost::Die(World* aWorld)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, 13, 13, myPath);
}

void Ghost::Update(float aTime, World* aWorld)
{
	int nextTileX = GetCurrentTileX() + myDesiredMovementX;
	int nextTileY = GetCurrentTileY() + myDesiredMovementY;

	if (myIsDeadFlag)
		speed = 120.f;

	animation_delta_time++;
	if (animation_delta_time == animation_time) {
		nextFrame = !nextFrame;
		animation_delta_time = 0;
	}

	if (IsAtDestination())
	{
		if (!myPath.empty())
		{
			PathmapTile* nextTile = myPath.front();
			myPath.pop_front();
			SetNextTile(nextTile->myX, nextTile->myY);
		}
		else if (aWorld->TileIsValid(nextTileX, nextTileY))
		{
			//SetNextTile(nextTileX, nextTileY); // Allow ghosts to move weirdly
		}
		else
		{
			if (myDesiredMovementX == 1)
			{
				myDesiredMovementX = 0;
				myDesiredMovementY = 1;
				eyePhase = "down";
			}
			else if (myDesiredMovementY == 1)
			{
				myDesiredMovementX = -1;
				myDesiredMovementY = 0;
				eyePhase = "left";
			}
			else if (myDesiredMovementX == -1)
			{
				myDesiredMovementX = 0;
				myDesiredMovementY = -1;
				eyePhase = "up";
			} 
			else
			{
				myDesiredMovementX = 1;
				myDesiredMovementY = 0;
				eyePhase = "right";
			}
			myIsDeadFlag = false;
		}
	}

	// Move the ghosts
	int tileSize = 22;
	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	float distanceToMove = aTime * speed * speedMultiplier;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}
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

	if (myIsDeadFlag) {
		//aDrawer->DrawResource(aDrawer->resources["ghost_test_dead"], (int)myPosition.myX + offsetX, (int)myPosition.myY + offsetY);
		aDrawer->DrawResource(aDrawer->resources["ghost_eyes_" + eyePhase], (int)myPosition.myX + offsetX, (int)myPosition.myY + offsetY);
	}
	else if (myIsClaimableFlag) {
		aDrawer->DrawResource(aDrawer->resources["ghost_vulnerable"], (int)myPosition.myX + offsetX, (int)myPosition.myY + offsetY);
		aDrawer->DrawResource(aDrawer->resources["ghost_vulnerable_feet_" + foot], (int)myPosition.myX + offsetX, (int)myPosition.myY + offsetY);
		aDrawer->DrawResource(aDrawer->resources["ghost_vulnerable_eyes"], (int)myPosition.myX + offsetX, (int)myPosition.myY + offsetY);
	}
	else {
		aDrawer->DrawResource(aDrawer->resources[activeResourceKey], (int)myPosition.myX + offsetX, (int)myPosition.myY + offsetY);
		aDrawer->DrawResource(aDrawer->resources["ghost_" + name + "_feet_" + foot], (int)myPosition.myX + offsetX, (int)myPosition.myY + offsetY);
		aDrawer->DrawResource(aDrawer->resources["ghost_eyes_" + eyePhase], (int)myPosition.myX + offsetX, (int)myPosition.myY + offsetY);
	}
}
