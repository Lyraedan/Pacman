#ifndef MENU_H
#define MENU_H

#include "Drawer.h"

#include <sstream>

class Drawer;

class Menu
{
public:
	Menu();
	~Menu(void);

	virtual void Update(float aTime);
	virtual void Draw(Drawer* aDrawer);

protected:
	int score = 0;
};
#endif // MENU_H
