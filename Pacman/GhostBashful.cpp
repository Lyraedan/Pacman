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

		int relativeX = 0;
		int relativeY = 0;

		Vector2f pacmanPos = Vector2f(pacman->GetCurrentTileX(), pacman->GetCurrentTileY());
		Vector2f shadowPosition = Vector2f(ghosts[0]->GetCurrentTileX(), ghosts[0]->GetCurrentTileY());
		float dotProduct = dot(pacmanPos, shadowPosition);

		nextPathX = isScattering ? scatterX : pacman->GetCurrentTileX();
		nextPathY = isScattering ? scatterY : pacman->GetCurrentTileY();
	}

	if (!aWorld->TileIsValid(nextPathX, nextPathY)) {
		nextPathX = scatterX;
		nextPathY = scatterY;
	}
}
