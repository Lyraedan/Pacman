#include "Menu.h"
#include "AudioPlayer.h"

class TitleMenu : public Menu
{
public:
	TitleMenu();
	~TitleMenu(void);

	void Update(float time);
	void Draw(Drawer* drawer);

private:
	void DrawGhostDetails(std::string ghost, std::string nickname, Drawer* drawer, int xOffset, int yOffset, SDL_Color fg);
	int enterFlickerTime = 0;
	int enterFlickerDelay = 100;
};

