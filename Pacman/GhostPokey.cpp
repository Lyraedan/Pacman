#include "GhostPokey.h"

GhostPokey::GhostPokey(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_pokey";
	name = "pokey";
}

GhostPokey::~GhostPokey(void)
{
}

void GhostPokey::Behaviour(World * aWorld, Avatar * pacman, Ghost * ghosts[4])
{
	//myPath.clear();
	//aWorld->GetPath(myCurrentTileX, myCurrentTileY, 0, 26, myPath);
}
