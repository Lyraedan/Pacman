#include "GhostShadow.h"

GhostShadow::GhostShadow(const Vector2f & position) : Ghost(position)
{
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

void GhostShadow::Behaviour(World * world, Avatar * pacman, Ghost * ghosts[4])
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
			Vector2f pacmanPosition = pacman->GetPosition();
			pacmanPosition /= 22;
			nextTile = pacmanPosition;
		}
	}

	if (!world->TileIsValid(nextTile.x, nextTile.y)) {
		nextTile = scatterPoints[0];
	}
}
