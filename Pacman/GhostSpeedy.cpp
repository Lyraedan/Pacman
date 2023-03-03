#include "GhostSpeedy.h"

GhostSpeedy::GhostSpeedy(const Vector2f & aPosition) : Ghost(aPosition)
{
	respawnX = aPosition.myX;
	respawnY = aPosition.myY;
	activeResourceKey = "ghost_speedy";
	name = "speedy";
	scatterPoints[0] = Vector2f(0, 0);
	scatterPoints[1] = Vector2f(5, 0);
	scatterPoints[2] = Vector2f(5, 4);
	scatterPoints[3] = Vector2f(0, 4);
	nextTile = scatterPoints[0];
}

GhostSpeedy::~GhostSpeedy(void)
{
}

void GhostSpeedy::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
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
			Vector2f target = OffsetFromPacman(pacman, 2);
			Vector2f pacmanPosition = pacman->myPosition;
			pacmanPosition /= 22;
			Vector2f tile = pacmanPosition + target;
			nextTile = tile;
		}
	}

	if (!aWorld->TileIsValid(nextTile.myX, nextTile.myY)) {
		nextTile = scatterPoints[0];
	}
}
