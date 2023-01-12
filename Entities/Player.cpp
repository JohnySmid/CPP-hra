#include "Player.h"
#include "../Colliders/BoxCollider.h"
#include "../Managers/PhyManager.h"

Player::Player()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instatnce();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 3;

	mSoldier = new Texture("PlayerTXT.png");
	mSoldier->SetParent(this);
	mSoldier->SetPos(Vec2_ZERO);	// centrovano na parent
	mMoveSpeed = 300.0f;
	// 1024x896
	mXMoveBounds = Vector2d(45.0f, 815.0f);
	mYMoveBounds = Vector2d(60.0f, 830.0f);

	mDeathAnimSoldier = new AnimatedTexture("PlayerDeadTXT.png", 0, 0, 128, 128, 4, 1.0f, AnimatedTexture::horizontal);
	mDeathAnimSoldier->SetParent(this);
	mDeathAnimSoldier->SetPos(Vec2_ZERO);
	mDeathAnimSoldier->WrapMode(AnimatedTexture::once);

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
	}

	AddCollider(new BoxCollider(Vector2d(90.0f, 90.0f)));
	mId = PhyManager::Instance()->RegisterEntity(this, PhyManager::CollisionLayers::Player);

}

Player::~Player()
{
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mSoldier;
	mSoldier = nullptr;
	delete mDeathAnimSoldier;
	mDeathAnimSoldier = nullptr;

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
}

bool Player::IgnoreCollision()
{
	if (WasHit())
		return true;
	else if (!mVisible)
		return true;
	else if (mAnimating)
		return true;
	//return !mVisible || mAnimating;
}

void Player::MoveHandler()
{


	if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		SetTranslate(Vec2_RIGHT * mMoveSpeed * mTimer->GetDeltaTime(), world);
	}

	if (mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		SetTranslate(-Vec2_RIGHT * mMoveSpeed * mTimer->GetDeltaTime(), world);
	}

	if (mInput->KeyDown(SDL_SCANCODE_UP))
	{
		SetTranslate(-Vec2_UP * mMoveSpeed * mTimer->GetDeltaTime(), world);
	}

	if (mInput->KeyDown(SDL_SCANCODE_DOWN))
	{
		SetTranslate(Vec2_UP * mMoveSpeed * mTimer->GetDeltaTime(), world);
	}

	Vector2d pos = GetPos(local);
	// X osa
	if (pos.x < mXMoveBounds.x)
		pos.x = mXMoveBounds.x;
	else if (pos.x > mXMoveBounds.y)
		pos.x = mXMoveBounds.y;
	// Y osa
	if (pos.y < mYMoveBounds.x)
		pos.y = mYMoveBounds.x;
	else if (pos.y > mYMoveBounds.y)
		pos.y = mYMoveBounds.y;

	SetPos(pos);
}

void Player::FireHandler()
{
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE))
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!mBullets[i]->GetActice())
			{
				mBullets[i]->Fire(GetPos());
				mAudio->PlaySFX("fire.wav");
				break;
			}
		}
	}
}

void Player::Hit(PhyEntity* other)
{
	//this->SetPos(Vector2d(Graphics::Instatnce()->SCREEM_WIDTH * 0.425f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.85f));		//nemam na to
	mLives--;
	mDeathAnimSoldier->ResetAnimation();
	mAnimating = true;
	mAudio->PlaySFX("roar.wav");
	mWasHit = true;
	printf("\n\n\nlives: %d\n", mLives);
}

bool Player::WasHit()
{
	return mWasHit;
}


void Player::IsVisible(bool vis)
{
	mVisible = vis;
}

bool Player::IsAnimating()
{
	return mAnimating;
}

int Player::GetScore()
{
	return mScore;
}

int Player::GetLives()
{
	return mLives;
}

void Player::AddScore(int score)
{
	mScore += score;
}

void Player::Update()
{
	if (mAnimating)
	{
		//printf("\nisanimating...\n");
		if (mWasHit)
		{
			//printf("hithithit\n");
			mWasHit = false;
			//printf("\nmWasHitFalse\n");
		}

		mDeathAnimSoldier->Update();
		mAnimating = mDeathAnimSoldier->IsAnimating();

	}
	else
	{
		if (GetActice())
		{
			MoveHandler();
			FireHandler();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
		mBullets[i]->Update();
}

void Player::Render()
{
	if (mVisible)
	{
		if (mAnimating)
		{
			//Animated player
			mDeathAnimSoldier->Render();
		}
		else
		{
			mSoldier->Render();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
		mBullets[i]->Render();

	PhyEntity::Render();
}