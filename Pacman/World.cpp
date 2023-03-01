#include "World.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "PathmapTile.h"
#include "Dot.h"
#include "BigDot.h"
#include "Cherry.h"
#include "Teleport.h"
#include "Drawer.h"

World::World(void)
{
}

World::~World(void)
{
}

void World::Init()
{
	InitMap();
	SpawnCherry();
}

bool World::InitMap()
{
	std::string line;
	std::ifstream myfile("map.txt");
	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (!myfile.eof())
		{
			std::getline(myfile, line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				PathmapTile* tile = new PathmapTile(i, lineIndex, (line[i] == 'x'));
				myPathmapTiles.push_back(tile);

				if (line[i] == '.') {
					Dot* dot = new Dot(Vector2f(i * 22, lineIndex * 22));
					myDots.push_back(dot);
				}
				else if (line[i] == 'o') {
					BigDot* dot = new BigDot(Vector2f(i * 22, lineIndex * 22));
					myBigDots.push_back(dot);
				}
				else if (line[i] == 'T') {
					Teleport* teleport = new Teleport(Vector2f(i * 22, lineIndex * 22));
					teleport->teleportIndex = teleports.size();
					teleports.push_back(teleport);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

bool World::SpawnCherry()
{
	cherry = new Cherry(Vector2f(13 * 22, 16 * 22));
	return true;
}

void World::Draw(Drawer* aDrawer)
{
	aDrawer->DrawResource(aDrawer->resources["map"]);
	
	// Rewrite these for loops

	for(std::list<Dot*>::iterator list_iter = myDots.begin(); list_iter != myDots.end(); list_iter++)
	{
		Dot* dot = *list_iter;
		dot->Draw(aDrawer);
	}

	for(std::list<BigDot*>::iterator list_iter = myBigDots.begin(); list_iter != myBigDots.end(); list_iter++)
	{
		BigDot* dot = *list_iter;
		dot->Update();
		dot->Draw(aDrawer);
	}

	if(!cherry->pickedup)
		cherry->Draw(aDrawer);
}

void World::Update() {
	cherry->canSpawn = (cherry->dotsEatenCount >= cherry->requiredDots);
	if (cherry->pickedup && cherry->canSpawn) {
		cherry->cherryRespawnTimer++;
		if (cherry->cherryRespawnTimer >= cherry->cherryRespawnDelay) {
			cherry->pickedup = false;
			cherry->cherryRespawnTimer = 0;
		}
	}
}

bool World::TileIsValid(int anX, int anY)
{
	for (PathmapTile* tile : myPathmapTiles) {
		if (anX == tile->myX && anY == tile->myY && !tile->myIsBlockingFlag)
			return true;
	}
	return false;
}

bool World::HasIntersectedDot(const Vector2f& aPosition)
{
	for (Dot* dot : myDots) {
		if ((dot->GetPosition() - aPosition).Length() < 5.f)
		{
			myDots.remove(dot);
			cherry->dotsEatenCount++;
			delete dot;
			return true;
		}
	}
	return false;
}

bool World::HasIntersectedCherry(const Vector2f& aPosition) {
	if (cherry->pickedup)
		return false;

	if ((cherry->GetPosition() - aPosition).Length() < 5.f) {
		cherry->pickedup = true;
		cherry->requiredDots += 100;
		return true;
	}
	return false;
}

Teleport* World::HasIntersectedTeleport(const Vector2f & aPosition)
{
	for(auto* teleport : teleports) {
		if ((teleport->GetPosition() - aPosition).Length() < 5.f)
		{
			return teleport;
		}
	}
	return NULL;
}

bool World::HasIntersectedBigDot(const Vector2f& aPosition)
{
	for(BigDot* dot : myBigDots)
	{
		if ((dot->GetPosition() - aPosition).Length() < 5.f)
		{
			myBigDots.remove(dot);
			cherry->dotsEatenCount++;
			delete dot;
			return true;
		}
	}

	return false;
}

void World::GetPath(int aFromX, int aFromY, int aToX, int aToY, std::list<PathmapTile*>& aList)
{
	PathmapTile* fromTile = GetTile(aFromX, aFromY);
	PathmapTile* toTile = GetTile(aToX, aToY);

	for(PathmapTile* tile : myPathmapTiles)
	{
		tile->myIsVisitedFlag = false;
	}

	Pathfind(fromTile, toTile, aList);
}

PathmapTile* World::GetTile(int aFromX, int aFromY)
{
	for (PathmapTile* tile : myPathmapTiles)
	{
		if (tile->myX == aFromX && tile->myY == aFromY)
		{
			return tile;
		}
	}

	return NULL;
}

bool World::ListDoesNotContain(PathmapTile* aFromTile, std::list<PathmapTile*>& aList)
{
	return !(std::find(aList.begin(), aList.end(), aFromTile) != aList.end());
}

bool SortFromGhostSpawn(PathmapTile* a, PathmapTile* b)
{
	int la = abs(a->myX - 13) + abs(a->myY - 13);
	int lb = abs(b->myX - 13) + abs(b->myY - 13);

    return la < lb;
}

bool World::Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, std::list<PathmapTile*>& aList)
{
	aFromTile->myIsVisitedFlag = true;

	if (aFromTile->myIsBlockingFlag)
		return false;

	if (aFromTile == aToTile)
		return true;

	std::list<PathmapTile*> neighborList;

	PathmapTile* up = GetTile(aFromTile->myX, aFromTile->myY - 1);
	if (up && !up->myIsVisitedFlag && !up->myIsBlockingFlag && ListDoesNotContain(up, aList)) {
		neighborList.push_front(up);
	}

	PathmapTile* down = GetTile(aFromTile->myX, aFromTile->myY + 1);
	if (down && !down->myIsVisitedFlag && !down->myIsBlockingFlag && ListDoesNotContain(down, aList)) {
		neighborList.push_front(down);
	}

	PathmapTile* right = GetTile(aFromTile->myX + 1, aFromTile->myY);
	if (right && !right->myIsVisitedFlag && !right->myIsBlockingFlag && ListDoesNotContain(right, aList)) {
		neighborList.push_front(right);
	}

	PathmapTile* left = GetTile(aFromTile->myX - 1, aFromTile->myY);
	if (left && !left->myIsVisitedFlag && !left->myIsBlockingFlag && ListDoesNotContain(left, aList)) {
		neighborList.push_front(left);
	}


	neighborList.sort(SortFromGhostSpawn);
	for (PathmapTile* tile : neighborList)
	{
		aList.push_back(tile);

		if (Pathfind(tile, aToTile, aList))
			return true;

		aList.pop_back();
	}
	return false;
}