#pragma once
#include "Ghost.h"
#include "World.h"
#include "Avatar.h"

class World;
class Avatar;

class GhostBashful : public Ghost
{
	public:
		GhostBashful(const Vector2f& aPosition);
		~GhostBashful(void);

		void Behaviour(World* aWorld, Avatar* pacman, Ghost* ghosts[4]);

	private:
		int currentPoint = 0;
		Vector2f topLeft = Vector2f(0, 0);
		Vector2f topRight = Vector2f(25, 0);
		Vector2f bottomLeft = Vector2f(0, 25);
		Vector2f bottomRight = Vector2f(25, 25);
		Vector2f nextPoint = topLeft;

		bool chasingPacman = false;
};

