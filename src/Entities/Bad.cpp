#include "Bad.h"
#include "../Colliders/BoxCollider.h"
#include "../Colliders/CircleCollider.h"
#include "../Managers/PhyManager.h"


Bad::Bad(int index)
	: Enemy(index)
{
	mTargetPosition = GetlocalPos();

	msTexture = new Texture("EnemyTXT.png");
	msTexture->SetParent(this);
	msTexture->SetPos(Vec2_ZERO);

	AddCollider(new BoxCollider(msTexture->ScaleDim()));
}

Bad::~Bad()
{}


Vector2d Bad::GetlocalPos()
{
	Vector2d retVal;

	retVal = GetPos();

	return retVal;
}

void Bad::Hit(PhyEntity* other)
{
	sPlayer->AddScore(1);
	Enemy::Hit(other);
}

void Bad::SpawnHandler()
{
	Enemy::SpawnHandler();
}

void Bad::DeathHandler()
{
	Enemy::DeathHandler();
}

void Bad::OnScreenHandler()
{
	Enemy::OnScreenHandler();
}


void Bad::Render()
{
	Enemy::Render();
}
