#ifndef CHERRY_H
#define CHERRY_H

#include "StaticGameEntity.h"
#include "Vector2f.h"

class Cherry : public StaticGameEntity
{
public:
	Cherry(Vector2f position);
	~Cherry(void);

	bool pickedup = true;
	int cherryRespawnTimer = 0;
	int cherryRespawnDelay = 100;
	int dotsEatenCount = 0;
	int requiredDots = 70;
	int canSpawn = true;
};

#endif // CHERRY_H