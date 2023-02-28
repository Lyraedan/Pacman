#include "GhostBashful.h"

GhostBashful::GhostBashful(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_bashful";
	name = "bashful";
	scatterX = 26;
	scatterY = 26;
}

GhostBashful::~GhostBashful(void)
{
}

void GhostBashful::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
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

	if (myPath.size() == 0) {
		if (!myIsDeadFlag) {
			aWorld->GetPath(myCurrentTileX, myCurrentTileY, nextPathX, nextPathY, myPath);
		}
	}
}
