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
		}
	}

	if (!aWorld->TileIsValid(nextPathX, nextPathY)) {
		nextPathX = scatterX;
		nextPathY = scatterY;
	}
}
