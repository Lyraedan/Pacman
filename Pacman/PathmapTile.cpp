#include "PathmapTile.h"

PathmapTile::PathmapTile(int x, int y, bool isSolid)
{
	this->x = x;
	this->y = y;
	this->isSolid = isSolid;
	isVisited = false;
}

PathmapTile::~PathmapTile(void)
{
}
