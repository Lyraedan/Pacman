#include "World.h"

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
	std::ifstream myfile("world/map.txt");
	int tileSize = 22;
	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (!myfile.eof())
		{
			std::getline(myfile, line);
			for (int i = 0; i < line.length(); i++)
			{
				PathmapTile* tile = new PathmapTile((float) i, (float) lineIndex, (line[i] == 'x'));
				mapTiles.push_back(tile);

				float x = (float) (i * tileSize);
				float y = (float) (lineIndex * tileSize);

				if (line[i] == '.') {
					Dot* dot = new Dot(Vector2f(x, y));
					dots.push_back(dot);
				}
				else if (line[i] == 'o') {
					BigDot* dot = new BigDot(Vector2f(x, y));
					bigDots.push_back(dot);
				}
				else if (line[i] == 'T') {
					Teleport* teleport = new Teleport(Vector2f(x, y));
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

void World::Draw(Drawer* drawer)
{
	drawer->DrawResource(drawer->resources["map"]);
	
	for(Dot* dot : dots)
	{
		dot->Draw(drawer);
	}

	for(BigDot* dot : bigDots)
	{
		dot->Update();
		dot->Draw(drawer);
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

bool World::TileIsValid(int x, int y)
{
	for (PathmapTile* tile : mapTiles) {
		if (x == tile->x && y == tile->y && !tile->isSolid)
			return true;
	}
	return false;
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

bool World::HasIntersectedCherry(const Vector2f& position) {
	if (cherry->pickedup)
		return false;

	if ((cherry->GetPosition() - position).Length() < 5.f) {
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

Teleport* World::HasIntersectedTeleport(const Vector2f & position)
{
	for(Teleport* teleport : teleports) {
		if ((teleport->GetPosition() - position).Length() < 5.f)
		{
			return teleport;
		}
	}
	return NULL;
}

bool World::HasIntersectedBigDot(const Vector2f& position)
{
	for(BigDot* dot : bigDots)
	{
		if ((dot->GetPosition() - position).Length() < 5.f)
		{
			bigDots.remove(dot);
			cherry->dotsEatenCount++;
			delete dot;
			return true;
		}
	}

	return false;
}

void World::GetPath(int fromX, int fromY, int toX, int toY, std::list<PathmapTile*>& path)
{
	PathmapTile* fromTile = GetTile(fromX, fromY);
	PathmapTile* toTile = GetTile(toX, toY);

	for(PathmapTile* tile : mapTiles)
	{
		tile->isVisited = false;
	}

	Pathfind(fromTile, toTile, path);
}

PathmapTile* World::GetTile(int x, int y)
{
	for (PathmapTile* tile : mapTiles)
	{
		if (tile->x == x && tile->y == y)
		{
			return tile;
		}
	}

	return NULL;
}

bool World::ListDoesNotContain(PathmapTile* fromTile, std::list<PathmapTile*>& path)
{
	return !(std::find(path.begin(), path.end(), fromTile) != path.end());
}

bool World::Pathfind(PathmapTile* fromTile, PathmapTile* toTile, std::list<PathmapTile*>& path)
{
	fromTile->isVisited = true;

	if (fromTile->isSolid)
		return false;

	if (fromTile == toTile)
		return true;

	std::list<PathmapTile*> neighbours;

	PathmapTile* up = GetTile(fromTile->x, fromTile->y - 1);
	if (up && !up->isVisited && !up->isSolid && ListDoesNotContain(up, path)) {
		neighbours.push_front(up);
	}

	PathmapTile* down = GetTile(fromTile->x, fromTile->y + 1);
	if (down && !down->isVisited && !down->isSolid && ListDoesNotContain(down, path)) {
		neighbours.push_front(down);
	}

	PathmapTile* right = GetTile(fromTile->x + 1, fromTile->y);
	if (right && !right->isVisited && !right->isSolid && ListDoesNotContain(right, path)) {
		neighbours.push_front(right);
	}

	PathmapTile* left = GetTile(fromTile->x - 1, fromTile->y);
	if (left && !left->isVisited && !left->isSolid && ListDoesNotContain(left, path)) {
		neighbours.push_front(left);
	}

	neighbours.sort([toTile](PathmapTile* a, PathmapTile* b) {
		if (toTile == nullptr)
			return false;

		float distanceA = (float) sqrt(pow(a->x - toTile->x, 2) +
								  pow(a->y - toTile->y, 2));


		float distanceB = (float) sqrt(pow(b->x - toTile->x, 2) +
							      pow(b->y - toTile->y, 2));

		return distanceA < distanceB;
	});

	for (PathmapTile* tile : neighbours)
	{
		path.push_back(tile);

		if (Pathfind(tile, toTile, path))
			return true;

		path.pop_back();
	}
	return false;
}