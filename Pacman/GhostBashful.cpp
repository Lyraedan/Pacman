#include "GhostBashful.h"

GhostBashful::GhostBashful(const Vector2f & aPosition) : Ghost(aPosition)
{
	respawnX = aPosition.myX;
	respawnY = aPosition.myY;
	activeResourceKey = "ghost_bashful";
	name = "bashful";
	scatterX = 25;
	scatterY = 26;
}

GhostBashful::~GhostBashful(void)
{
}

void GhostBashful::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
{
	if (myPath.size() == 0) {
		if (!myIsDeadFlag) {
			aWorld->GetPath(myCurrentTileX, myCurrentTileY, nextPathX, nextPathY, myPath);
		}
	}

	if (myIsClaimableFlag) {
		if (!myIsDeadFlag) {
			nextPathX = scatterX;
			nextPathY = scatterY;
		}
	}
	else {
		if (initialSetup) {
			int changeX = 0;
			int changeY = 0;

			if (pacman->direction.myX == 1)
				changeX = 2;
			else if (pacman->direction.myY == 1)
				changeY = 2;
			else if (pacman->direction.myX == -1)
				changeX = -2;
			else if (pacman->direction.myY == -1)
				changeY = -2;

			int targetX = (pacman->GetCurrentTileX() + changeX);
			int targetY = (pacman->GetCurrentTileY() + changeY);

			Vector2f target = Vector2f(targetX, targetY);
			Vector2f direction = target - ghosts[0]->myPosition;
			direction *= 2;

			int tileX = abs(direction.myX);
			int tileY = abs(direction.myY);

			nextPathX = tileX / 35;
			nextPathY = tileY / 35;

			/*
			float distanceFromPacman = aWorld->DistanceFrom(pacman->myPosition, myPosition);

			chasingPacman = distanceFromPacman < (8 * 22);

			if (HasReachedEndOfPath() && !myIsDeadFlag && !chasingPacman) {
				currentPoint++;
				if (currentPoint >= 4)
					currentPoint = 0;
			}

			switch (currentPoint) {
			case 0:
				nextPoint = topLeft;
				break;
			case 1:
				nextPoint = topRight;
				break;
			case 2:
				nextPoint = bottomRight;
				break;
			case 3:
				nextPoint = bottomLeft;
				break;
			}

			int x = chasingPacman ? pacman->GetCurrentTileX() : nextPoint.myX;
			int y = chasingPacman ? pacman->GetCurrentTileY() : nextPoint.myY;

			nextPathX = isScattering ? scatterX : x;
			nextPathY = isScattering ? scatterY : y;
			*/
		}
	}

	if (!aWorld->TileIsValid(nextPathX, nextPathY)) {
		nextPathX = scatterX;
		nextPathY = scatterY;
	}
}
