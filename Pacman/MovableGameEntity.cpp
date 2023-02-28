#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(const Vector2f& aPosition)
: GameEntity(aPosition)
{
	myCurrentTileX = myNextTileX =  myPosition.myX / 22;
	myCurrentTileY = myNextTileY =  myPosition.myY / 22;
}

MovableGameEntity::~MovableGameEntity(void)
{
}

void MovableGameEntity::TeleportTo(int x, int y, int nextX, int nextY)
{
	myCurrentTileX = x;
	myCurrentTileY = y;
	SetNextTile(nextX, nextY);
}

bool MovableGameEntity::IsAtDestination()
{
	return myCurrentTileX == myNextTileX && myCurrentTileY == myNextTileY;
}

void MovableGameEntity::SetNextTile(int anX, int anY)
{
	myNextTileX = anX;
	myNextTileY = anY;
}
