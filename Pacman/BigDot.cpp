#include "BigDot.h"

BigDot::BigDot(Vector2f aPosition)
: StaticGameEntity(aPosition)
{
	activeResourceKey = "bigdot";
}

BigDot::~BigDot(void)
{
}
