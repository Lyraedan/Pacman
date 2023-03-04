#include "GameEntity.h"
#include "Drawer.h"

GameEntity::GameEntity(const Vector2f& position)
{
	SetPosition(position);
}

GameEntity::~GameEntity(void)
{
}

void GameEntity::Update() {

}

void GameEntity::Draw(Drawer* drawer)
{
	Vector2f position = GetPosition();
	int x = (int) position.x + 220;
	int y = (int) position.y + 60;
	drawer->DrawResource(drawer->resources[activeResourceKey], x, y);
}
