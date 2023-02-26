#include "Dot.h"

Dot::Dot(Vector2f aPosition)
: StaticGameEntity(aPosition)
{
	activeResourceKey = "dot";
}

Dot::~Dot(void)
{
}
