#include "GhostPokey.h"

GhostPokey::GhostPokey(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_pokey";
	name = "pokey";
	scatterX = 0;
	scatterY = 26;
}

GhostPokey::~GhostPokey(void)
{
}

void GhostPokey::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
{
	if (myPath.size() == 0) {
		if (!myIsDeadFlag) {
			aWorld->GetPath(myCurrentTileX, myCurrentTileY, nextPathX, nextPathY, myPath);
		}
	}

	if (myIsClaimableFlag) {
		nextPathX = scatterX;
		nextPathY = scatterY;
	}
	else {
		if (initialSetup) {
			float distanceFromPacman = aWorld->DistanceFrom(pacman->myPosition, myPosition);

			bool inRangeOfPacman = distanceFromPacman < (8 * 22);

			nextPathX = isScattering ? scatterX : pacman->GetCurrentTileX();
			nextPathY = isScattering ? scatterY : pacman->GetCurrentTileY();

			if (!flee && inRangeOfPacman) {
				ClearPath();
				nextPathX = scatterX;
				nextPathY = scatterY;
				flee = true;
			}
		}
	}

	if (!aWorld->TileIsValid(nextPathX, nextPathY)) {
		nextPathX = scatterX;
		nextPathY = scatterY;
	}

	if (HasReachedEndOfPath() && flee) {
		flee = false;
	}
}
