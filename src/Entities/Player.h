#pragma once
#include <vector>
#include "Textures/AnimatedTexture.h"
#include "Bullet.h"
#include "../Managers/InputManager.h"
#include "../Managers/AudioManager.h"

class Player : public PhyEntity
{
public:
	Player();
	~Player();

	void IsVisible(bool v);

	void Hit(PhyEntity* other) override;
	bool WasHit();

	bool IsAnimating();

	int GetScore();
	int GetLives();
	void AddScore(int score);




	void Update();
	void Render();
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;
	bool IgnoreCollision() override;

	int mScore;
	int mLives;

	Texture* mSoldier;
	AnimatedTexture* mDeathAnimSoldier;

	static const int MAX_BULLETS = 3;
	Bullet* mBullets[MAX_BULLETS];

	float mMoveSpeed;
	Vector2d mXMoveBounds;
	Vector2d mYMoveBounds;

	void MoveHandler();
	void FireHandler();
};

