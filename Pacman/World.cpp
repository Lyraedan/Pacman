#include "World.h"
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
				mapTiles.push_back(tile);

				if (line[i] == '.') {
					Dot* dot = new Dot(Vector2f(i * 22, lineIndex * 22));
					dots.push_back(dot);
				}
				else if (line[i] == 'o') {
					BigDot* bigDot = new BigDot(Vector2f(i * 22, lineIndex * 22));
					bigDots.push_back(bigDot);
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
	cherry = new Cherry(Vector2f(13, 16));
	return true;
}

void World::Draw(Drawer* drawer)
{
	drawer->DrawResource(drawer->resources["map"]);

	if (drawMapTiles) {
		for (PathmapTile* tile : mapTiles) {
			Vector2f tilePosition = tile->GetPosition();
			tilePosition *= 22;
			int x = tilePosition.x + 220;
			int y = tilePosition.y + 60;
			drawer->DrawResource(drawer->resources[tile->isSolid ? "target" : "target_free"], x, y);
		}
	}
	
	for(Dot* dot : dots)
	{
		dot->Draw(drawer);
	}

	for(BigDot* bigDot : bigDots)
	{
		// Only call update here because it handles the dot flashing
		bigDot->Update();
		bigDot->Draw(drawer);
	}

	if(!cherry->pickedup)
		cherry->Draw(drawer);
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

bool World::TileIsValid(Vector2f& position)
{
	for (PathmapTile* tile : mapTiles) {
		Vector2f tilePosition = tile->GetPosition();

		float x = roundf(position.x);
		float y = roundf(position.y);

		if (x == tilePosition.x && y == tilePosition.y && !tile->isSolid)
			return true;
	}
	return false;
}

PathmapTile * World::GetNearestTileTo(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= 25)
		x = 25;
	if (y < 0)
		y = 0;
	else if (y >= 27)
		y = 27;

	return GetTile(Vector2f(x, y));
}

bool World::HasIntersectedDot(const Vector2f& position)
{
	for (Dot* dot : dots) {
		if ((dot->GetPosition() - position).Length() < 5.f)
		{
			dots.remove(dot);
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

bool World::HasIntersectedPacman(const Ghost* ghost, const Avatar* pacman)
{
	return (ghost->GetPosition() - pacman->GetPosition()).Length() < 5.f;
}

Teleport* World::HasIntersectedTeleport(const Vector2f & aPosition)
{
	for(Teleport* teleport : teleports) {
		if ((teleport->GetPosition() - aPosition).Length() < 5.f)
		{
			return teleport;
		}
	}
	return NULL;
}

bool World::HasIntersectedBigDot(const Vector2f& aPosition)
{
	for(BigDot* dot : bigDots)
	{
		if ((dot->GetPosition() - aPosition).Length() < 5.f)
		{
			bigDots.remove(dot);
			cherry->dotsEatenCount++;
			delete dot;
			return true;
		}
	}

	return false;
}

void World::GetPath(Vector2f from, Vector2f to, std::list<PathmapTile*>& aList)
{
	PathmapTile* fromTile = GetTile(from);
	PathmapTile* toTile = GetTile(to);

	for(PathmapTile* tile : mapTiles)
	{
		tile->isVisited = false;
	}

	Pathfind(fromTile, toTile, aList);
}

PathmapTile* World::GetTile(Vector2f at)
{
	for (PathmapTile* tile : mapTiles)
	{
		Vector2f position = tile->GetPosition();
		if (position.x == at.x && position.y == at.y) {
			return tile;
		}
	}

	return NULL;
}

bool World::ListDoesNotContain(PathmapTile* from, std::list<PathmapTile*>& currentPath)
{
	return !(std::find(currentPath.begin(), currentPath.end(), from) != currentPath.end());
}

bool World::Pathfind(PathmapTile* from, PathmapTile* to, std::list<PathmapTile*>& currentPath)
{
	if (from == nullptr || to == nullptr)
		return false;

	from->isVisited = true;

	if (from->isSolid)
		return false;

	Vector2f fromPosition = from->GetPosition();
	Vector2f toPosition = to->GetPosition();

	if (from == to)
		return true;

	std::list<PathmapTile*> neighborList;

	// Check neighbouring tiles and add any that are avaliable to the neighbor list
	PathmapTile* up = GetTile(Vector2f(fromPosition.x, fromPosition.y - 1));
	if (up && !up->isVisited && !up->isSolid && ListDoesNotContain(up, currentPath)) {
		neighborList.push_front(up);
	}

	PathmapTile* down = GetTile(Vector2f(fromPosition.x, fromPosition.y + 1));
	if (down && !down->isVisited && !down->isSolid && ListDoesNotContain(down, currentPath)) {
		neighborList.push_front(down);
	}

	PathmapTile* right = GetTile(Vector2f(fromPosition.x + 1, fromPosition.y));
	if (right && !right->isVisited && !right->isSolid && ListDoesNotContain(right, currentPath)) {
		neighborList.push_front(right);
	}

	PathmapTile* left = GetTile(Vector2f(fromPosition.x - 1, fromPosition.y));
	if (left && !left->isVisited && !left->isSolid && ListDoesNotContain(left, currentPath)) {
		neighborList.push_front(left);
	}

	// Sort the neighbours by chosing the next tile closest to the target
	neighborList.sort([to](PathmapTile* a, PathmapTile* b) {
		if (to == nullptr)
			return false;

		Vector2f aPosition = a->GetPosition();
		Vector2f bPosition = b->GetPosition();
		Vector2f toPosition = to->GetPosition();

		float distanceA = sqrt(pow(aPosition.x - toPosition.x, 2) +
							   pow(aPosition.y - toPosition.y, 2));


		float distanceB = sqrt(pow(bPosition.x - toPosition.x, 2) +
							   pow(bPosition.y - toPosition.y, 2));

		return distanceA < distanceB;
	});

	for (PathmapTile* tile : neighborList)
	{
		currentPath.push_back(tile);

		if (Pathfind(tile, to, currentPath))
			return true;

		currentPath.pop_back();
	}
	return false;
}