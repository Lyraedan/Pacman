#include "Avatar.h"

Avatar::Avatar(const Vector2f& aPosition)
	: MovableGameEntity(aPosition)
{
	activeResourceKey = "pacman_right_open";
}

Avatar::~Avatar(void)
{
}

void Avatar::Update(float aTime)
{
	int tileSize = 22;

	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	float distanceToMove = aTime * 30.f * movementSpeed;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}

	// Animate
	std::string state = open ? "open" : "closed";
	std::string facing = "right";
	bool transition = animation_delta_time > (animation_time / 2);

	animation_delta_time++;
	if (animation_delta_time == animation_time) {
		open = !open;
		animation_delta_time = 0;
	}

	if (myNextMovement == move_up) {
		facing = "up";
	}
	else if (myNextMovement == move_down) {
		facing = "down";
	}
	else if (myNextMovement == move_left) {
		facing = "left";
	}
	else if (myNextMovement == move_right) {
		facing = "right";
	}

	const std::string resourceKey = transition == true ? "pacman_" + facing + "_" + state : // pacman_up_open / pacman_up_closed
														 "pacman_transition_" + facing; // pacman_transition_up
	activeResourceKey = resourceKey;
}
