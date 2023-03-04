#pragma once
#include "Ghost.h"
#include "World.h"
#include "Avatar.h"

class World;
class Avatar;

class GhostSpeedy : public Ghost
{
	public:
		GhostSpeedy(const Vector2f& position);
		~GhostSpeedy(void);

		void Behaviour(World* world, Avatar* pacman, Ghost* ghosts[4]);
};

