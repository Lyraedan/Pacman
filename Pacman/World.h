#ifndef WORLD_H
#define WORLD_H

#include <list>
#include "Vector2f.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "PathmapTile.h"
#include "Ghost.h"
#include "Avatar.h"
#include "Dot.h"
#include "BigDot.h"
#include "Cherry.h"
#include "Teleport.h"
#include "Drawer.h"

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
	bool TileIsValid(int x, int y);

	bool HasIntersectedDot(const Vector2f& position);
	bool HasIntersectedBigDot(const Vector2f& position);
	bool HasIntersectedCherry(const Vector2f& position);
	bool HasIntersectedPacman(const Ghost* ghost, const Avatar* pacman);
	Teleport* HasIntersectedTeleport(const Vector2f& position);

	void Update();

	void GetPath(int fromX, int fromY, int toX, int toY, std::list<PathmapTile*>& path);

	int DotsCount() {
		return dots.size();
	};

	int BigDotsCount() {
		return dots.size();
	}

	float DistanceFrom(Vector2f src, Vector2f dest) {
		return sqrt(pow(dest.x - src.x, 2) +
			   pow(dest.y - src.y, 2));
	}

	Cherry* cherry;

private:

	PathmapTile* GetTile(int fromX, int fromY);
	bool Pathfind(PathmapTile* fromTile, PathmapTile* toTile, std::list<PathmapTile*>& path);
	bool ListDoesNotContain(PathmapTile* fromTile, std::list<PathmapTile*>& path);

	std::list<PathmapTile*> mapTiles;
	std::list<Dot*> dots;
	std::list<BigDot*> bigDots;
	std::list<Teleport*> teleports;

	bool InitMap();
	bool SpawnCherry();

};

#endif // WORLD_H