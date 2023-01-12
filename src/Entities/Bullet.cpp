#include "Bullet.h"
#include "../Colliders/BoxCollider.h"
#include "../Managers/PhyManager.h"

Bullet::Bullet()
{
	mTimer = Timer::Instance();

	mSpeed = 500.0f;

	// --- Bullet ---
	mBulletTXT = new Texture("BulletTXT.png");
	mBulletTXT->SetParent(this);
	mBulletTXT->SetPos(Vec2_ZERO);

	Reload();

	// --- Collider ---
	AddCollider(new BoxCollider(mBulletTXT->ScaleDim()));
	mId = PhyManager::Instance()->RegisterEntity(this, PhyManager::CollisionLayers::PlayerBullets);
}

Bullet::~Bullet()
{
	mTimer = nullptr;
	delete mBulletTXT;
	mBulletTXT = nullptr;
}

void Bullet::Hit(PhyEntity* other)
{
	Reload();
}

bool Bullet::IgnoreCollision()
{
	return !GetActice();
}

void Bullet::Fire(Vector2d pos)
{
	SetPos(pos);
	SetActive(true);
}
void Bullet::Reload()
{
	SetActive(false);
}

void Bullet::Update()
{
	if (GetActice())
	{
		SetTranslate(-Vec2_UP * mSpeed * mTimer->GetDeltaTime(), local);

		Vector2d pos = GetPos();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instatnce()->SCREEN_HEIGHT + OFFSCREEN_BUFFER)
			Reload();
	}
}
void Bullet::Render()
{
	if (GetActice())
	{
		mBulletTXT->Render();
		PhyEntity::Render();
	}
}