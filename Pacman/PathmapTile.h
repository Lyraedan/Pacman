#ifndef PATHMAPTILE_H
#define PATHMAPTILE_H

#include "Vector2f.h"

class Vector2f;

class PathmapTile
{
public:
	PathmapTile(int anX, int anY, bool aIsBlockingFlag);
	~PathmapTile(void);

	int myX;
	int myY;
	Vector2f myPosition() {
		return Vector2f(myX, myY);
	}
	bool myIsBlockingFlag;
	bool myIsVisitedFlag;

};

#endif // PATHMAPTILE_H