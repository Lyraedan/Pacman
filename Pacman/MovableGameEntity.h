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

	void TeleportTo(int x, int y, int nextX, int nextY);

	bool IsAtDestination();

	void UpdatePosition(Vector2f next) {
		position += next;
	}

protected:

	Vector2f nextTile;
	Vector2f currentTile;

};

#endif // MOVABLEGAMEENTITY_H