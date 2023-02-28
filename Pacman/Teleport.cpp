#include "Teleport.h"

Teleport::Teleport(Vector2f aPosition) 
	: StaticGameEntity(aPosition) 
{
	activeResourceKey = "cherry";
}

Teleport::~Teleport(void)
{
}
