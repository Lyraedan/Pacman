#include "TitleMenu.h"

TitleMenu::TitleMenu() : Menu() {

}

TitleMenu::~TitleMenu(void)
{
}

void TitleMenu::Update(float time)
{
}

void TitleMenu::Draw(Drawer * drawer)
{
	drawer->DrawResource(drawer->resources["title"], 248, 50);

	int ghostsOffsetX = 350;
	int ghostsOffsetY = 300;
	float spacing = 1.5f;
	DrawGhostDetails("shadow", "\"Blinky\"", drawer, ghostsOffsetX, ghostsOffsetY);
	DrawGhostDetails("speedy", "\"Pinky\"", drawer, ghostsOffsetX, ghostsOffsetY + (32 * spacing));
	DrawGhostDetails("bashful", "\"Inky\"", drawer, ghostsOffsetX, ghostsOffsetY + (64 * spacing));
	DrawGhostDetails("pokey", "\"Clyde\"", drawer, ghostsOffsetX, ghostsOffsetY + (96 * spacing));
	drawer->DrawText("Press [SPACE] to start!", "font-joystix\\Joystix.ttf", 350, 200);
}

void TitleMenu::DrawGhostDetails(std::string ghost, const char* nickname, Drawer * drawer, int xOffset, int yOffset)
{
	drawer->DrawResource(drawer->resources["ghost_" + ghost], xOffset, yOffset);
	drawer->DrawResource(drawer->resources["ghost_" + ghost + "_feet_a"], xOffset, yOffset);
	drawer->DrawResource(drawer->resources["ghost_eyes_right"], xOffset, yOffset);
	drawer->DrawText(nickname, "font-joystix\\Joystix.ttf", xOffset + 40, yOffset + 8);
}
