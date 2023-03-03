#include "GhostBashful.h"

GhostBashful::GhostBashful(const Vector2f & aPosition) : Ghost(aPosition)
{
	respawnX = aPosition.myX;
	respawnY = aPosition.myY;
	activeResourceKey = "ghost_bashful";
	name = "bashful";
	scatterPoints[0] = Vector2f(25, 26);
	scatterPoints[1] = Vector2f(20, 27);
	scatterPoints[2] = Vector2f(14, 26);
	scatterPoints[3] = Vector2f(19, 22);
	nextTile = scatterPoints[0];
}

GhostBashful::~GhostBashful(void)
{
}

void GhostBashful::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
{
	if (myPath.size() == 0) {
		if (!myIsDeadFlag) {
			aWorld->GetPath(myCurrentTileX, myCurrentTileY, nextTile.myX, nextTile.myY, myPath);
		}
	}

	if ((isScattering || myIsClaimableFlag) && HasReachedEndOfPath()) {
		currentScatterIndex++;
	}

	if (myIsClaimableFlag || isScattering) {
		if (!myIsDeadFlag) {
			nextTile = scatterPoints[currentScatterIndex % 4];
		}
	}
	else {
		if (initialSetup) {
			Vector2f pacmanPosition = pacman->myPosition;
			Vector2f shadowPosition = ghosts[0]->myPosition;
			pacmanPosition /= 22;
			shadowPosition /= 22;

			Vector2f target = pacmanPosition + OffsetFromPacman(pacman, 2);
			Vector2f direction = shadowPosition - target;
			Vector2f tile = target + direction;
			nextTile = Vector2f(tile.myX, tile.myY);
		}
	}

	if (!aWorld->TileIsValid(nextTile.myX, nextTile.myY)) {
		nextTile = scatterPoints[0];
	}
}
