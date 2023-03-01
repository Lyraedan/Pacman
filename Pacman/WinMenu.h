#include "Menu.h"

class WinMenu : public Menu
{
public:
	WinMenu(int score);
	~WinMenu(void);

	void Update(float time);
	void Draw(Drawer* drawer);
};

