#ifndef PATHMAPTILE_H
#define PATHMAPTILE_H

#include "Vector2f.h"

class Vector2f;

class PathmapTile
{
public:
	PathmapTile(int x, int y, bool isSolid);
	~PathmapTile(void);

	int x;
	int y;
	Vector2f GetPosition() {
		return Vector2f((float) x, (float) y);
	}
	bool isSolid;
	bool isVisited;

};

#endif // PATHMAPTILE_H