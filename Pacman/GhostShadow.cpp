#include "GhostShadow.h"

GhostShadow::GhostShadow(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_shadow";
	name = "shadow";
}

GhostShadow::~GhostShadow(void)
{
}

void GhostShadow::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
{
	//myPath.clear();
	//aWorld->GetPath(myCurrentTileX, myCurrentTileY, 26, 0, myPath);
}
