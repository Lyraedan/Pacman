#pragma once
#include "Ghost.h"
#include "World.h"
#include "Avatar.h"

class World;
class Avatar;

class GhostShadow : public Ghost
{
	public:
		GhostShadow(const Vector2f& position);
		~GhostShadow(void);

		void Behaviour(World* world, Avatar* pacman, Ghost* ghosts[4]);

};

