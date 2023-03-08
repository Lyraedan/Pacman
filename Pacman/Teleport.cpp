#include "Teleport.h"

Teleport::Teleport(Vector2f position) : StaticGameEntity(position)
{
	activeResourceKey = "";
}

Teleport::~Teleport(void)
{
}
