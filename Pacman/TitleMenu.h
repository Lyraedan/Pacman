#include "Menu.h"

class TitleMenu : public Menu
{
public:
	TitleMenu();
	~TitleMenu(void);

	void Update(float time);
	void Draw(Drawer* drawer);

private:
	void DrawGhostDetails(std::string ghost, const char* nickname, Drawer* drawer, int xOffset, int yOffset);
};

