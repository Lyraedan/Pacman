#include "GhostSpeedy.h"

GhostSpeedy::GhostSpeedy(const Vector2f & aPosition) : Ghost(aPosition)
{
	activeResourceKey = "ghost_speedy";
	name = "speedy";
}

GhostSpeedy::~GhostSpeedy(void)
{
}