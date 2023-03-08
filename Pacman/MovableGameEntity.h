#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"

class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(const Vector2f& position);
	~MovableGameEntity(void);

	void SetNextTile(int x, int y);
	
	int GetCurrentTileX() const 
	{
		return currentTileX; 
	}

	int GetCurrentTileY() const 
	{
		return currentTileY; 
	}

	void TeleportTo(int x, int y, int nextX, int nextY);

	bool IsAtDestination();

protected:

	// current tile coordinates scaled to the grid
	int currentTileX;
	int currentTileY;

	// Next tile coordinates scaled to the grid
	int nextTileX;
	int nextTileY;

};

#endif // MOVABLEGAMEENTITY_H