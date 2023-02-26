#include "GhostBashful.h"

GhostBashful::GhostBashful(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_bashful";
	name = "bashful";
}

GhostBashful::~GhostBashful(void)
{
}