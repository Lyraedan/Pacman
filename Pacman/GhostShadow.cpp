#include "GhostShadow.h"

GhostShadow::GhostShadow(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_shadow";
	name = "shadow";
}

GhostShadow::~GhostShadow(void)
{
}