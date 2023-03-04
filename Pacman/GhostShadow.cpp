#include "GhostShadow.h"

GhostShadow::GhostShadow(const Vector2f & position) : Ghost(position)
{
	respawn = position;
	currentTile = position;
	activeResourceKey = "ghost_shadow";
	name = "shadow";
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
	if (currentPath.empty()) {
		if (!isDead) {
			world->GetPath(currentTile, nextTile, currentPath);
		}
	}

	if (isScattering || isVulnerable) {
		Vector2f currentScatterPoint = scatterPoints[currentScatterIndex % 4];
		if (!world->TileIsValid(currentScatterPoint)) {
			currentScatterIndex++;
		}
		if (currentTile == currentScatterPoint) {
			currentScatterIndex++;
		}
	}

	if (isVulnerable || isScattering) {
		if (!isDead) {
			nextTile = scatterPoints[currentScatterIndex % 4];
		}
	}
	else {
		if (initialSetup) {
			Vector2f pacmanPosition = pacman->GetPositionAsGridCoordinates();
			nextTile = pacmanPosition;
		}
	}

	if (!world->TileIsValid(nextTile)) {
		nextTile = scatterPoints[0];
	}
}
