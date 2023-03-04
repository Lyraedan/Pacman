#pragma once
#include "Ghost.h"
#include "World.h"
#include "Avatar.h"

class World;
class Avatar;

class GhostBashful : public Ghost
{
	public:
		GhostBashful(const Vector2f& position);
		~GhostBashful(void);

		void Behaviour(World* world, Avatar* pacman, Ghost* ghosts[4]);
};

