#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"
#include "Drawer.h"

#include <sstream>
#include <functional>

class Drawer;

class Avatar : public MovableGameEntity
{
public:
	Avatar(const Vector2f& position);
	~Avatar(void);

	void Update(float delta);

	void Die(std::function<void()> afterSequance);

	Vector2f nextMovement;
	Vector2f direction;

	Vector2f move_left = Vector2f(-1.f, 0.f);
	Vector2f move_right = Vector2f(1.f, 0.f);
	Vector2f move_up = Vector2f(0.f, -1.f);
	Vector2f move_down = Vector2f(0.f, 1.f);

	bool dieAnimation = false;

private:
	bool open = true;
	const std::string facing = "right";
	int animation_delta_time = 0;
	int animation_time = 30;
	float movementSpeed = 5.f;

	int death_animation_delta_time = 0;
	int death_animation_time = 30;
	int currentDeathFrame = 0;
};

#endif //AVATAR_H