#include "GhostBashful.h"

GhostBashful::GhostBashful(const Vector2f & position) : Ghost(position)
{
	activeResourceKey = "ghost_bashful";
	name = "bashful";
	myPath.clear();
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
			Vector2f shadowPosition = ghosts[0]->GetPosition();
			pacmanPosition /= 22;
			shadowPosition /= 22;

			Vector2f target = pacmanPosition + OffsetFromPacman(pacman, 2);
			Vector2f direction = shadowPosition - target;
			Vector2f tile = target + direction;
			nextTile = Vector2f(tile.x, tile.y);
		}
	}

	if (!world->TileIsValid(nextTile.x, nextTile.y)) {
		nextTile = scatterPoints[0];
	}
}
