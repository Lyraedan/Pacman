#include "Teleport.h"

Teleport::Teleport(Vector2f aPosition) 
	: StaticGameEntity(aPosition) 
{
	activeResourceKey = "";
}

Teleport::~Teleport(void)
{
}
