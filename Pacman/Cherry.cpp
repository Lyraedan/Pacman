#include "Cherry.h"

Cherry::Cherry(Vector2f position) : StaticGameEntity(position)
{
	activeResourceKey = "cherry";
	Vector2f spawn = position;
	spawn *= 22;
	SetPosition(spawn);
}

Cherry::~Cherry(void)
{
}
