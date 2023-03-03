#include "TitleMenu.h"

TitleMenu::TitleMenu() : Menu() 
{
	AudioPlayer::PlayWav("demosound.wav");
}

TitleMenu::~TitleMenu(void)
{
}

void TitleMenu::Update(float time)
{
	enterFlickerTime++;
	if (enterFlickerTime >= enterFlickerDelay) {
		enterFlickerTime = 0;
	}
}

void TitleMenu::Draw(Drawer * drawer)
{
	drawer->DrawResource(drawer->resources["title"], 248, 50);

	int ghostsOffsetX = 350;
	int ghostsOffsetY = 300;
	float spacing = 1.5f;
	DrawGhostDetails("shadow", "\"Blinky\"", drawer, ghostsOffsetX, ghostsOffsetY, { 255, 0, 0, 255 });
	DrawGhostDetails("speedy", "\"Pinky\"", drawer, ghostsOffsetX, ghostsOffsetY + (32 * spacing), { 252, 181, 255, 255 });
	DrawGhostDetails("bashful", "\"Inky\"", drawer, ghostsOffsetX, ghostsOffsetY + (64 * spacing), { 0, 255, 255, 255 });
	DrawGhostDetails("pokey", "\"Clyde\"", drawer, ghostsOffsetX, ghostsOffsetY + (96 * spacing), { 248, 187, 85, 255 });
	drawer->DrawText(enterFlickerTime <= (enterFlickerDelay / 2) ? "" : "Press [SPACE] to start!", "font-joystix\\Joystix.ttf", 350, 200, { 255, 255, 255, 255 });

	drawer->DrawText("Luke Rapkin", "font-joystix\\Joystix.ttf", 5, 740, { 255, 255, 255, 255 });
}

void TitleMenu::DrawGhostDetails(std::string ghost, std::string nickname, Drawer * drawer, int xOffset, int yOffset, SDL_Color fg)
{
	drawer->DrawResource(drawer->resources["ghost_" + ghost], xOffset, yOffset);
	drawer->DrawResource(drawer->resources["ghost_" + ghost + "_feet_a"], xOffset, yOffset);
	drawer->DrawResource(drawer->resources["ghost_eyes_right"], xOffset, yOffset);

	drawer->DrawText((ghost + " " + nickname).c_str(), "font-joystix\\Joystix.ttf", xOffset + 40, yOffset + 8, fg);
}
