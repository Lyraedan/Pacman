#ifndef WORLD_H
#define WORLD_H

#include <list>
#include "Vector2f.h"

class Drawer;
class PathmapTile;
class Avatar;
class Ghost;
class Dot;
class BigDot;
class Cherry;
class Teleport;
class Vector2f;

class World
{
public:
	World(void);
	~World(void);

	void Init();

	void Draw(Drawer* aDrawer);
	bool TileIsValid(int anX, int anY);
	PathmapTile* GetNearestTileTo(int x, int y);

	bool HasIntersectedDot(const Vector2f& aPosition);
	bool HasIntersectedBigDot(const Vector2f& aPosition);
	bool HasIntersectedCherry(const Vector2f& aPosition);
	bool HasIntersectedPacman(const Ghost* ghost, const Avatar* pacman);
	Teleport* HasIntersectedTeleport(const Vector2f& aPosition);

	void Update();

	void GetPath(int aFromX, int aFromY, int aToX, int aToY, std::list<PathmapTile*>& aList);

	int DotsCount() {
		return myDots.size();
	};

	int BigDotsCount() {
		return myDots.size();
	}

	float DistanceFrom(Vector2f src, Vector2f dest) {
		return sqrt(pow(dest.myX - src.myX, 2) +
			   pow(dest.myY - src.myY, 2));
	}

	Cherry* cherry;

private:

	PathmapTile* GetTile(int aFromX, int aFromY);
	bool Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, std::list<PathmapTile*>& aList);
	bool ListDoesNotContain(PathmapTile* aFromTile, std::list<PathmapTile*>& aList);

	std::list<PathmapTile*> myPathmapTiles;
	std::list<Dot*> myDots;
	std::list<BigDot*> myBigDots;
	std::list<Teleport*> teleports;

	bool InitMap();
	bool SpawnCherry();

};

#endif // WORLD_H