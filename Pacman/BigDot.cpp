#include "BigDot.h"

BigDot::BigDot(Vector2f position) : StaticGameEntity(position)
{
	activeResourceKey = "bigdot";
}

BigDot::~BigDot(void)
{
}

void BigDot::Update()
{
	flashTimer++;
	activeResourceKey = (flashTimer >= flashDelay / 2) ? "" : "bigdot";
	if (flashTimer >= flashDelay) {
		flashTimer = 0;
	}
}
