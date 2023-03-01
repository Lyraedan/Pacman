#include "WinMenu.h"

WinMenu::WinMenu(int score) : Menu()
{
	this->score = score;
}

WinMenu::~WinMenu(void)
{

}

void WinMenu::Update(float time)
{
	enterFlickerTime++;
	if (enterFlickerTime >= enterFlickerDelay) {
		enterFlickerTime = 0;
	}
}

void WinMenu::Draw(Drawer * drawer)
{
	drawer->DrawResource(drawer->resources["win"], 248, 50);

	int scoreX = 300;
	int scoreY = 200;
	drawer->DrawText("You scored:", "font-joystix\\Joystix.ttf", scoreX, scoreY, { 255, 255, 255, 255 });

	std::string scoreString;
	std::stringstream scoreStream;
	scoreStream << score;
	scoreString = scoreStream.str();
	drawer->DrawText(scoreString.c_str(), "font-joystix\\Joystix.ttf", scoreX + 180, scoreY, { 255, 255, 255, 255 });

	drawer->DrawText(enterFlickerTime <= (enterFlickerDelay / 2) ? "" : "Press [ESCAPE] to exit!", "font-joystix\\Joystix.ttf", scoreX, scoreY + 32, { 255, 255, 255, 255 });
}
