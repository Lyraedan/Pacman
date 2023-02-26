#pragma once
#include "Ghost.h"
class GhostShadow : public Ghost
{
	public:
		GhostShadow(const Vector2f& aPosition);
		~GhostShadow(void);
		void Update(float aTime, World * aWorld);
};

