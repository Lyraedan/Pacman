#pragma once
#include "Ghost.h"
#include "World.h"
#include "Avatar.h"

class World;
class Avatar;

class GhostPokey : public Ghost
{
	public:
		GhostPokey(const Vector2f& position);
		~GhostPokey(void);

		void Behaviour(World* world, Avatar* pacman, Ghost* ghosts[4]);

private:
	bool flee = false;
};

