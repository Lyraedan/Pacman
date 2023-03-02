#include "GhostSpeedy.h"

GhostSpeedy::GhostSpeedy(const Vector2f & aPosition) : Ghost(aPosition)
{
	respawnX = aPosition.myX;
	respawnY = aPosition.myY;
	activeResourceKey = "ghost_speedy";
	name = "speedy";
	scatterX = 0;
	scatterY = 1;
	nextPathX = scatterX;
	nextPathY = scatterY;
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
		if (!myIsDeadFlag) {
			nextPathX = scatterX;
			nextPathY = scatterY;
		}
	}
	else {
		if (initialSetup) {
			Vector2f target = PositionRelativeToPacman(pacman, 2);
			nextPathX = isScattering ? scatterX : (pacman->GetCurrentTileX() + target.myX);
			nextPathY = isScattering ? scatterY : (pacman->GetCurrentTileY() + target.myY);
		}
	}

	if (!aWorld->TileIsValid(nextPathX, nextPathY)) {
		nextPathX = scatterX;
		nextPathY = scatterY;
	}
}
