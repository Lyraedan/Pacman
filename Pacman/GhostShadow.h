#pragma once
#include "Ghost.h"
#include "World.h"
#include "Avatar.h"

class World;
class Avatar;

class GhostShadow : public Ghost
{
	public:
		GhostShadow(const Vector2f& aPosition);
		~GhostShadow(void);

		void Behaviour(World* aWorld, Avatar* pacman, Ghost* ghosts[4]);
};

