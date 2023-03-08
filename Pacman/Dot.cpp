#include "Dot.h"

Dot::Dot(Vector2f position) : StaticGameEntity(position)
{
	activeResourceKey = "dot";
}

Dot::~Dot(void)
{
}
