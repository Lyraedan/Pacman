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

	Vector2f GetPosition() const { 
		return position;
	}

	void SetPosition(const Vector2f& position) {
		this->position = position;
	}

	void SetPositionAsGridCoordinate(const Vector2f& position) {
		SetPosition(Vector2f(position.x * 22, position.y * 22));
	}

	Vector2f GetPositionAsGridCoordinates() {
		Vector2f pos = position;
		pos /= 22;
		return pos;
	}

	void Update();
	virtual void Draw(Drawer* drawer);

protected:
	Vector2f position;
	std::string activeResourceKey;

};

#endif // GAMEENTITY_H