#include "PathmapTile.h"

PathmapTile::PathmapTile(int x, int y, bool isSolid)
{
	position = Vector2f(x, y);
	this->isSolid = isSolid;
	isVisited = false;
}

PathmapTile::~PathmapTile(void)
{
}
