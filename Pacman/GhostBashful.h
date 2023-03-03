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
};

