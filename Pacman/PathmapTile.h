#ifndef PATHMAPTILE_H
#define PATHMAPTILE_H

#include "Vector2f.h"

class Vector2f;

class PathmapTile
{
public:
	PathmapTile(int x, int y, bool isSolid);
	~PathmapTile(void);

	Vector2f GetPosition() {
		return position;
	}
	bool isSolid;
	bool isVisited;

private:
	Vector2f position;

};

#endif // PATHMAPTILE_H