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

	void Draw(Drawer* drawer);
	bool TileIsValid(Vector2f& position);
	PathmapTile* GetNearestTileTo(int x, int y);

	bool HasIntersectedDot(const Vector2f& position);
	bool HasIntersectedBigDot(const Vector2f& position);
	bool HasIntersectedCherry(const Vector2f& position);
	bool HasIntersectedPacman(const Ghost* ghost, const Avatar* pacman);
	Teleport* HasIntersectedTeleport(const Vector2f& position);

	void Update();

	void GetPath(Vector2f from, Vector2f to, std::list<PathmapTile*>& currentPath);

	int DotsCount() {
		return dots.size();
	};

	int BigDotsCount() {
		return bigDots.size();
	}

	float DistanceFrom(Vector2f src, Vector2f dest) {
		return sqrt(pow(dest.x - src.x, 2) +
					pow(dest.y - src.y, 2));
	}

	Cherry* cherry;

private:

	PathmapTile* GetTile(Vector2f position);
	bool Pathfind(PathmapTile* from, PathmapTile* to, std::list<PathmapTile*>& currentPath);
	bool ListDoesNotContain(PathmapTile* from, std::list<PathmapTile*>& currentPath);

	std::list<PathmapTile*> mapTiles;
	std::list<Dot*> dots;
	std::list<BigDot*> bigDots;
	std::list<Teleport*> teleports;

	bool InitMap();
	bool SpawnCherry();

};

#endif // WORLD_H