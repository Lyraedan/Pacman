#ifndef BIGDOT_H
#define BIGDOT_H

#include "StaticGameEntity.h"
#include "Vector2f.h"

class BigDot : public StaticGameEntity
{
public:
	BigDot(Vector2f aPosition);
	~BigDot(void);

	void Update();

private:
	int flashTimer = 0;
	int flashDelay = 100;
};

#endif // BIGDOT_H