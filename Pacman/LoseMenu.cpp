#include "LoseMenu.h"

LoseMenu::LoseMenu(int score) : Menu()
{
	this->score = score;
}

LoseMenu::~LoseMenu(void)
{
}

void LoseMenu::Update(float time)
{
}

void LoseMenu::Draw(Drawer * drawer)
{
	drawer->DrawResource(drawer->resources["gameover"], 248, 50);

	int scoreX = 300;
	int scoreY = 200;
	drawer->DrawText("You scored:", "font-joystix\\Joystix.ttf", scoreX, scoreY);

	std::string scoreString;
	std::stringstream scoreStream;
	scoreStream << score;
	scoreString = scoreStream.str();
	drawer->DrawText(scoreString.c_str(), "font-joystix\\Joystix.ttf", scoreX + 180, scoreY);

	drawer->DrawText("Press [ESCAPE] to exit.", "font-joystix\\Joystix.ttf", scoreX, scoreY + 32);
}
