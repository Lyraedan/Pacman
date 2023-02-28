#include "GhostSpeedy.h"

GhostSpeedy::GhostSpeedy(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_speedy";
	name = "speedy";
}

GhostSpeedy::~GhostSpeedy(void)
{
}

void GhostSpeedy::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
{
	//myPath.clear();
	//aWorld->GetPath(myCurrentTileX, myCurrentTileY, 0, 26, myPath);
}
