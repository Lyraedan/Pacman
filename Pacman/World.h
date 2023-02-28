#ifndef WORLD_H
#define WORLD_H

#include <list>
#include "Vector2f.h"

class Drawer;
class PathmapTile;
class Dot;
class BigDot;
class Cherry;
class Teleport;

class World
{
public:
	World(void);
	~World(void);

	void Init();

	void Draw(Drawer* aDrawer);
	bool TileIsValid(int anX, int anY);

	bool HasIntersectedDot(const Vector2f& aPosition);
	bool HasIntersectedBigDot(const Vector2f& aPosition);
	bool HasIntersectedCherry(const Vector2f& aPosition);
	Teleport* HasIntersectedTeleport(const Vector2f& aPosition);

	void Update();

	void GetPath(int aFromX, int aFromY, int aToX, int aToY, std::list<PathmapTile*>& aList);

	int DotsCount() {
		return myDots.size();
	};

	int BigDotsCount() {
		return myDots.size();
	}

private:

	PathmapTile* GetTile(int aFromX, int aFromY);
	bool Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, std::list<PathmapTile*>& aList);
	bool ListDoesNotContain(PathmapTile* aFromTile, std::list<PathmapTile*>& aList);

	std::list<PathmapTile*> myPathmapTiles;
	std::list<Dot*> myDots;
	std::list<BigDot*> myBigDots;
	Cherry* cherry;
	std::list<Teleport*> teleports;

	bool InitMap();
	bool SpawnCherry();

};

#endif // WORLD_H