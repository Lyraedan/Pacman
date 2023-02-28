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
	if (myIsClaimableFlag) {
		nextPathX = scatterX;
		nextPathY = scatterY;
	}
	else {
		nextPathX = isScattering ? scatterX : pacman->GetCurrentTileX();
		nextPathY = isScattering ? scatterY : pacman->GetCurrentTileY();
	}

	if (!aWorld->TileIsValid(nextPathX, nextPathY)) {
		nextPathX = scatterX;
		nextPathY = scatterY;
	}

	if (HasReachedEndOfPath()) {
		myPath.clear();
	}
	if (myPath.size() == 0) {
		if (!myIsDeadFlag) {
			aWorld->GetPath(myCurrentTileX, myCurrentTileY, nextPathX, nextPathY, myPath);
		}
	}
}
