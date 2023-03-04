#include "GhostSpeedy.h"

GhostSpeedy::GhostSpeedy(const Vector2f & position) : Ghost(position)
{
	respawn = position;
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

void GhostSpeedy::Behaviour(World * world, Avatar * pacman, Ghost * ghosts[4])
{
	if (currentPath.size() == 0) {
		if (!isDead) {
			world->GetPath(currentTile, nextTile, currentPath);
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
			Vector2f target = OffsetFromPacman(pacman, 2);
			Vector2f pacmanPosition = pacman->GetPositionAsGridCoordinates();
			Vector2f tile = pacmanPosition + target;
			nextTile = tile;
		}
	}

	if (!world->TileIsValid(nextTile)) {
		nextTile = scatterPoints[0];
	}
}
