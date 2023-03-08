#include "GhostSpeedy.h"

GhostSpeedy::GhostSpeedy(const Vector2f & position) : Ghost(position)
{
	activeResourceKey = "ghost_speedy";
	name = "speedy";
	myPath.clear();
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
	if (myPath.size() == 0) {
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
			Vector2f target = OffsetFromPacman(pacman, 2);
			Vector2f pacmanPosition = pacman->GetPosition();
			pacmanPosition /= 22;
			Vector2f tile = pacmanPosition + target;
			nextTile = tile;
		}
	}

	if (!world->TileIsValid(nextTile.x, nextTile.y)) {
		nextTile = scatterPoints[0];
	}
}
