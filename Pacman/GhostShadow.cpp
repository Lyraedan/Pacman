#include "GhostShadow.h"

GhostShadow::GhostShadow(const Vector2f & aPosition) : Ghost(aPosition)
{
	respawnX = aPosition.myX;
	respawnY = aPosition.myY;
	activeResourceKey = "ghost_shadow";
	name = "shadow";
	myPath.clear();
	scatterPoints[0] = Vector2f(25, 1);
	scatterPoints[1] = Vector2f(22, 3);
	scatterPoints[2] = Vector2f(20, 1);
	scatterPoints[3] = Vector2f(22, 0);
	nextTile = scatterPoints[0];
}

GhostShadow::~GhostShadow(void)
{
}

void GhostShadow::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
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
			pacmanPosition /= 22;
			nextTile = pacmanPosition;
		}
	}

	if (!aWorld->TileIsValid(nextTile.myX, nextTile.myY)) {
		nextTile = scatterPoints[0];
	}
}
