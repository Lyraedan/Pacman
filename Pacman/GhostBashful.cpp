#include "GhostBashful.h"

GhostBashful::GhostBashful(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_bashful";
	name = "bashful";
}

GhostBashful::~GhostBashful(void)
{
}

void GhostBashful::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
{
	//myPath.clear();
	//aWorld->GetPath(myCurrentTileX, myCurrentTileY, 26, 26, myPath);
}
