#pragma once
#include "Enemy.h"
class Bad : public Enemy
{
public:
	Bad(int index);
	~Bad();
	void Render();
private:
	Vector2d GetlocalPos();
	void Hit(PhyEntity* other) override;
	void SpawnHandler();
	void DeathHandler();
	void OnScreenHandler();

};

