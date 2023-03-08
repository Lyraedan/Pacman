#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Vector2f.h"
#include <string>

class Drawer;

class GameEntity
{
public:
	GameEntity(const Vector2f& position);
	~GameEntity(void);

	Vector2f GetPosition() const 
	{
		return position;
	}

	void Update();
	virtual void Draw(Drawer* drawer);

	Vector2f position;

protected:

	std::string activeResourceKey;
};

#endif // GAMEENTITY_H