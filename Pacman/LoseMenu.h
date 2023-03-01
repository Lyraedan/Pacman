#include "Menu.h"

class LoseMenu : public Menu
{
public:
	LoseMenu(int score);
	~LoseMenu(void);

	void Update(float time);
	void Draw(Drawer* drawer);
};

