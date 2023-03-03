#include "GhostPokey.h"

GhostPokey::GhostPokey(const Vector2f & aPosition) : Ghost(aPosition)
{
	respawnX = aPosition.myX;
	respawnY = aPosition.myY;
	activeResourceKey = "ghost_pokey";
	name = "pokey";
	scatterPoints[0] = Vector2f(0, 26);
	scatterPoints[1] = Vector2f(7, 22);
	scatterPoints[2] = Vector2f(11, 26);
	scatterPoints[3] = Vector2f(6, 27);
	nextTile = scatterPoints[0];
}

GhostPokey::~GhostPokey(void)
{
}

void GhostPokey::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
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
			float distanceFromPacman = aWorld->DistanceFrom(pacman->myPosition, myPosition);

			bool inRangeOfPacman = distanceFromPacman < (8 * 22);

			if (!flee) {
				Vector2f pacmanPosition = pacman->myPosition;
				pacmanPosition /= 22;
				nextTile = pacmanPosition;

				if (inRangeOfPacman) {
					ClearPath();
					currentScatterIndex++;
					nextTile = scatterPoints[currentScatterIndex % 4];
					flee = true;
				}
			}
		}
	}

	if (!aWorld->TileIsValid(nextTile.myX, nextTile.myY)) {
		nextTile = scatterPoints[0];
	}

	if (HasReachedEndOfPath() && flee) {
		flee = false;
	}
}
