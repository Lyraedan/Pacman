#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(const Vector2f& position) : GameEntity(position)
{
	//myCurrentTileX = myNextTileX =  myPosition.myX / 22;
	//myCurrentTileY = myNextTileY =  myPosition.myY / 22;
	/*
	SetNextTile(position.x, position.y);
	currentTile = nextTile;
	Vector2f newPosition = position;
	newPosition /= 22;
	this->SetPosition(newPosition);
	*/
	Vector2f spawnTile = position;
	spawnTile /= 22;
	currentTile = spawnTile;
	nextTile = currentTile;
	SetPosition(currentTile);
}

MovableGameEntity::~MovableGameEntity(void)
{
}

void MovableGameEntity::TeleportTo(int x, int y, int nextX, int nextY)
{
	SetPositionAsGridCoordinate(Vector2f(x, y));
	currentTile = Vector2f(x, y);
	SetNextTile(nextX, nextY);
}

bool MovableGameEntity::IsAtDestination()
{
	return currentTile == nextTile;
}

void MovableGameEntity::SetNextTile(int x, int y)
{
	nextTile = Vector2f(x, y);
}
