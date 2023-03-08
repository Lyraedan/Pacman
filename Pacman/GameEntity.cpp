#include "GameEntity.h"
#include "Drawer.h"

GameEntity::GameEntity(const Vector2f& position)
{
	this->position = position;
}

GameEntity::~GameEntity(void)
{
}

void GameEntity::Update() {

}

void GameEntity::Draw(Drawer* drawer)
{
	drawer->DrawResource(drawer->resources[activeResourceKey], (int)position.x + 220, (int)position.y + 60);
}
