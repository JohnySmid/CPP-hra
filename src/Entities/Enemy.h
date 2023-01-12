#pragma once
#include "Textures/AnimatedTexture.h"
#include "PhyEntity.h"
#include "Player.h"
#include <vector>

class Enemy : public PhyEntity
{
public:
	Enemy(int index);
	virtual ~Enemy();

	virtual void SpawnHandler();
	virtual void DeathHandler();
	virtual void OnScreenHandler();

	void StateHandler();
	int GetIndex();

	bool isBadDead();
	bool IgnoreCollision() override;


	void Hit(PhyEntity* other) override;

	static void CurPlayer(Player* pl);

	enum STATE
	{
		spawn,
		onscreen,
		dead
	};
	STATE GetCurrentState();

	void Update();

	virtual void Render();


protected:
	static Player* sPlayer;

	Timer* mTimer;
	std::vector<Texture*> mTexture;


	Texture* msTexture;

	STATE mCurrentState;
	int mIndex;
	float mSpeed;
	Vector2d mTargetPosition;

	bool mInitialized;
};

