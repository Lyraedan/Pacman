#include "GhostSpeedy.h"

GhostSpeedy::GhostSpeedy(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_speedy";
	name = "speedy";
	scatterX = 0;
	scatterY = 0;
}

GhostSpeedy::~GhostSpeedy(void)
{
}

void GhostSpeedy::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
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

			nextPathX = isScattering ? scatterX : (pacman->GetCurrentTileX() + changeX);
			nextPathY = isScattering ? scatterY : (pacman->GetCurrentTileY() + changeY);
		}
	}

	if (!aWorld->TileIsValid(nextPathX, nextPathY)) {
		nextPathX = scatterX;
		nextPathY = scatterY;
	}
}
