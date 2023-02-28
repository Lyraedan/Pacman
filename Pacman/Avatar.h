#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"

class Avatar : public MovableGameEntity
{
public:
	Avatar(const Vector2f& aPosition);
	~Avatar(void);

	void Update(float aTime);

	Vector2f myNextMovement;
	Vector2f direction;

	Vector2f move_left = Vector2f(-1.f, 0.f);
	Vector2f move_right = Vector2f(1.f, 0.f);
	Vector2f move_up = Vector2f(0.f, -1.f);
	Vector2f move_down = Vector2f(0.f, 1.f);


private:
	bool open = true;
	const std::string facing = "right";
	int animation_delta_time = 0;
	int animation_time = 30;
	float movementSpeed = 5.f;
};

#endif //AVATAR_H