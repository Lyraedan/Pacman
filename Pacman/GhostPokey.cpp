#include "GhostPokey.h"

GhostPokey::GhostPokey(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_pokey";
	name = "pokey";
}

GhostPokey::~GhostPokey(void)
{
}