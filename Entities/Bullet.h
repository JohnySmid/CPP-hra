#pragma once
#include "PhyEntity.h"
#include "../Helpers/Timer.h"


class Bullet : public PhyEntity
{
public:
	Bullet();
	~Bullet();

	void Fire(Vector2d pos);
	void Reload();

	void Hit(PhyEntity* other) override;

	void Update();
	void Render();

private:
	const int OFFSCREEN_BUFFER = 10;	// pixel off screen

	Timer* mTimer;

	float mSpeed;

	Texture* mBulletTXT;

	bool IgnoreCollision() override;
};

