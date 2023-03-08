#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(const Vector2f& position) : GameEntity(position)
{
	currentTileX = position.x / 22;
	currentTileY = position.y / 22;
	nextTileX = currentTileX;
	nextTileY = currentTileY;
}

MovableGameEntity::~MovableGameEntity(void)
{
}

void MovableGameEntity::TeleportTo(int x, int y, int nextX, int nextY)
{
	position.x = x * 22;
	position.y = y * 22;
	currentTileX = x;
	currentTileY = y;
	SetNextTile(nextX, nextY);
}

bool MovableGameEntity::IsAtDestination()
{
	return currentTileX == nextTileX && currentTileY == nextTileY;
}

void MovableGameEntity::SetNextTile(int x, int y)
{
	nextTileX = x;
	nextTileY = y;
}
