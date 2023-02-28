#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Vector2f.h"
#include <string>

class Drawer;

class GameEntity
{
public:
	GameEntity(const Vector2f& aPosition);
	~GameEntity(void);

	Vector2f GetPosition() const { return myPosition; }
	void SetPosition(const Vector2f& aPosition){ myPosition = aPosition; }

	bool Intersect(GameEntity* aGameEntity);
	void Update();
	virtual void Draw(Drawer* aDrawer);

	void MarkForDelete() { myIdMarkedForDeleteFlag = true; }
	bool IsMarkedForDelete() const { return myIdMarkedForDeleteFlag; }

protected:

	bool myIdMarkedForDeleteFlag;
	Vector2f myPosition;
	std::string activeResourceKey;
};

#endif // GAMEENTITY_H