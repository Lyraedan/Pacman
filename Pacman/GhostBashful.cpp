#include "GhostBashful.h"

GhostBashful::GhostBashful(const Vector2f & aPosition) : Ghost(aPosition)
{
	respawnX = aPosition.myX;
	respawnY = aPosition.myY;
	activeResourceKey = "ghost_bashful";
	name = "bashful";
	scatterX = 25;
	scatterY = 26;
	nextPathX = scatterX;
	nextPathY = scatterY;
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
			Vector2f pacmanPosition = pacman->myPosition;
			pacmanPosition /= 22;
			Vector2f target = pacmanPosition + OffsetFromPacman(pacman, 2);
			Vector2f shadowPosition = ghosts[0]->myPosition;
			shadowPosition /= 22;
			Vector2f direction = shadowPosition - target;
			Vector2f tile = target + direction;

			nextPathX = tile.myX;
			nextPathY = tile.myY;
		}
	}

	if (!aWorld->TileIsValid(nextPathX, nextPathY)) {
		nextPathX = scatterX;
		nextPathY = scatterY;
	}
}
