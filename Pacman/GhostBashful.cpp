#include "GhostBashful.h"

GhostBashful::GhostBashful(const Vector2f & position) : Ghost(position)
{
	respawn = position;
	currentTile = position;
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

void GhostBashful::Behaviour(World * world, Avatar * pacman, Ghost * ghosts[4])
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
			Vector2f shadowPosition = ghosts[0]->GetPositionAsGridCoordinates();

			Vector2f target = pacmanPosition + OffsetFromPacman(pacman, 2);
			Vector2f direction = shadowPosition - target;
			Vector2f tile = target + direction;
			nextTile = tile;
		}
	}

	if (!world->TileIsValid(nextTile)) {
		nextTile = scatterPoints[0];
	}
}
