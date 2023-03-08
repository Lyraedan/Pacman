#include "Menu.h"

class LoseMenu : public Menu
{
public:
	LoseMenu(int score);
	~LoseMenu(void);

	void Update(float delta);
	void Draw(Drawer* drawer);

private:
	int enterFlickerTime = 0;
	int enterFlickerDelay = 100;
};

