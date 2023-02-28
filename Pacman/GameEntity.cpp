#include "GameEntity.h"
#include "Drawer.h"

GameEntity::GameEntity(const Vector2f& aPosition)
:myPosition(aPosition)
,myIdMarkedForDeleteFlag(false)
{
}

GameEntity::~GameEntity(void)
{
}

bool GameEntity::Intersect(GameEntity* aGameEntity)
{

	return false;	
}

void GameEntity::Update() {

}

void GameEntity::Draw(Drawer* aDrawer)
{
	aDrawer->DrawResource(aDrawer->resources[activeResourceKey], (int)myPosition.myX + 220, (int)myPosition.myY + 60);
}
