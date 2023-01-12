#include "Enemy.h"
#include "../Managers/PhyManager.h"

Player* Enemy::sPlayer = nullptr;

void Enemy::CurPlayer(Player* pl)
{
	sPlayer = pl;
}

Enemy::Enemy(int index)
{
	mTimer = Timer::Instance();

	mCurrentState = spawn;


	// --- Random Spawn on top of the screen ---
	float r = 0.08 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.75 - 0.08)));
	SetPos(Vector2d(Graphics::Instatnce()->SCREEM_WIDTH * r, -10.0f));


	// --- Collider ---
	mId = PhyManager::Instance()->RegisterEntity(this, PhyManager::CollisionLayers::Enemy);
	mInitialized = false;

}

Enemy::~Enemy()
{
	mTimer = nullptr;
}

bool Enemy::IgnoreCollision()
{
	return mCurrentState == dead;
}

void Enemy::Hit(PhyEntity* other)
{
	//printf("\nEnemyHit");
	mCurrentState = dead;
}

bool Enemy::isBadDead()
{
	if (!GetActice())
		if (!mInitialized)
		{
			mInitialized = true;
			return true;
		}
	return false;
}

Enemy::STATE Enemy::GetCurrentState()
{
	return mCurrentState;
}

int Enemy::GetIndex()
{
	return mIndex;
}

void Enemy::SpawnHandler()
{
	if (GetActice())
	{
		mCurrentState = onscreen;
	}
}

void Enemy::OnScreenHandler()
{
	Vector2d pos = GetPos();

	if (pos.y > Graphics::Instatnce()->SCREEN_HEIGHT)
	{
		//printf("\npos: %f", pos.y);
		mCurrentState = dead;
	}


	SetTranslate(Vector2d(0.0f, 1.0f) * 100.0f * mTimer->GetDeltaTime(), world);
}

void Enemy::DeathHandler()
{
	this->SetActive(false);
}

void Enemy::StateHandler()
{
	switch (mCurrentState)
	{
	case spawn:
		SpawnHandler();
		break;
	case onscreen:
		OnScreenHandler();
		break;
	case dead:
		DeathHandler();
		break;
	}

}


void Enemy::Update()
{
	if (GetActice())
		StateHandler();

	if (mCurrentState == onscreen)
		OnScreenHandler();


}

void Enemy::Render()
{
	if (mCurrentState == onscreen)
	{
		msTexture->Render();
		PhyEntity::Render();
	}
}