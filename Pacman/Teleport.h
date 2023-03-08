#ifndef TELEPORT_H
#define TELEPORT_H

#include "StaticGameEntity.h"
#include "Vector2f.h"

class Teleport : public StaticGameEntity
{
public:
	Teleport(Vector2f position);
	~Teleport(void);

	int teleportIndex;
};
#endif // TELEPORT_H
