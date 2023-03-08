#include "GhostPokey.h"

GhostPokey::GhostPokey(const Vector2f & position) : Ghost(position)
{
	activeResourceKey = "ghost_pokey";
	name = "pokey";
	myPath.clear();
	scatterPoints[0] = Vector2f(0, 26);
	scatterPoints[1] = Vector2f(7, 22);
	scatterPoints[2] = Vector2f(11, 26);
	scatterPoints[3] = Vector2f(6, 27);
	nextTile = scatterPoints[0];
}

GhostPokey::~GhostPokey(void)
{
}

void GhostPokey::Behaviour(World * world, Avatar * pacman, Ghost * ghosts[4])
{
	if (myPath.empty()) {
		if (!isDead) {
			world->GetPath(currentTileX, currentTileY, nextTile.x, nextTile.y, myPath);
		}
	}

	if ((isScattering || isVulnerable) && HasReachedEndOfPath()) {
		currentScatterIndex++;
	}

	if (isVulnerable || isScattering) {
		if (!isDead) {
			nextTile = scatterPoints[currentScatterIndex % 4];
		}
	}
	else {
		if (initialSetup) {
			float distanceFromPacman = world->DistanceFrom(pacman->GetPosition(), GetPosition());

			bool inRangeOfPacman = distanceFromPacman < (8 * 22);

			if (!flee) {
				Vector2f pacmanPosition = pacman->GetPosition();
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

	if (!world->TileIsValid(nextTile.x, nextTile.y)) {
		nextTile = scatterPoints[0];
	}

	if (HasReachedEndOfPath() && flee) {
		flee = false;
	}
}
