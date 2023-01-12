#include "Level.h"

int Level::mBadLimit = 5;

Level::Level(int lvl, PlayBar* playbar, Player* player)
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instatnce();
	mPlayBar = playbar;
	mPlayBar->SetGameLvl(lvl);
	
	// --- Level init ---
	mCurStage = lvl;
	mLvlStarted = false;

	mLabelTimer = 0.0f;

	mLvlLabel = new Texture("Level:", "SEAS.ttf", 32, { 150, 150, 0 });
	mLvlLabel->SetParent(this);
	mLvlLabel->SetPos(Vector2d(Graphics::Instatnce()->SCREEM_WIDTH * 0.425f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.5f));

	mLvlNum = new ScoreBoard({ 150, 150, 0 });
	mLvlNum->SetScore(mCurStage);
	mLvlNum->SetParent(this);
	mLvlNum->SetPos(Vector2d(Graphics::Instatnce()->SCREEM_WIDTH * 0.550f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.5f));

	mLvlLabelOnScreen = 0.0f;		//ihned
	mLvlLabelOffScreen = 2.0f;		//2s po

	mLvlReadyLabel = new Texture("READY", "SEAS.ttf", 32, { 150, 150, 0 });
	mLvlReadyLabel->SetParent(this);
	mLvlReadyLabel->SetPos(Vector2d(Graphics::Instatnce()->SCREEM_WIDTH * 0.425f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.5f));

	mLvlReadyOnScreen = mLvlLabelOffScreen;
	mLvlReadyOffScreen = mLvlReadyOnScreen + 1.5f;

	mPlayer = player;
	mPlayerHit = false;
	mPlayerRespawnDelay = 2.0f; //2s
	mPlayerRespawnTimer = 0.0f;
	mPlayerRespawnLabelOnScreen = 1.0f;
	Enemy::CurPlayer(mPlayer);		//nastavime pro enemy hrace => pro pridavani skore


	// --- Game over label ---
	mGameOverLabel = new Texture("GAME OVER", "SEAS.ttf", 32, { 150, 150, 0 });
	mGameOverLabel->SetParent(this);
	mGameOverLabel->SetPos(Vector2d(Graphics::Instatnce()->SCREEM_WIDTH * 0.425f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	mGameOverDelay = 5.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f; //kdy se to ukaze


	// --- State ---
	mCurrentState = running;


	// --- Enemy spawn ---
	mBadCount = 0;
	mSpawningFinished = false;
	mSpawnTimer = 0.0f;
	mSpawnDelay = 1.0f;


}

Level::~Level()
{
	mTimer = nullptr;
	mPlayBar = nullptr;
	mPlayer = nullptr;
	mInput = nullptr;
	delete mLvlLabel;
	mLvlLabel = nullptr;
	delete mLvlNum;
	mLvlNum = nullptr;
	delete mLvlReadyLabel;
	mLvlReadyLabel = nullptr;
	delete mGameOverLabel;
	mGameOverLabel = nullptr;
	for (int i = 0; i < mEnemies.size(); i++)
	{
		delete mEnemies[i];
		mEnemies[i] = nullptr;
	}
}

void Level::StartLevel()
{
	mLvlStarted = true;
	//printf("lvl started");
}

void Level::HandleEnemySpawning()
{
	mSpawnTimer += mTimer->GetDeltaTime();
	if (mSpawnTimer >= mSpawnDelay)
	{
		while (true)
		{
			mEnemies.push_back(new Bad(mBadCount));

			mBadCount++;
			mSpawnTimer = 0.0f;


			break;
		}

	}
	else if (mBadCount == mBadLimit)
	{
		mSpawningFinished = true;
		mBadLimit += 5;
	}

	//if (mInput->KeyPressed(SDL_SCANCODE_W) && mBadCount < 10)
	//{
	//	mEnemies.push_back(new Bad(mBadCount));
	//	mBadCount++;
	//}
}

void Level::HandleEnemyDiving()
{
	bool lvlCleared = mSpawningFinished;

	for (int i = 0; i < mEnemies.size(); i++)
	{
		if (mEnemies[i]->GetCurrentState() != Enemy::dead)
		{
			//dokud nejsou vsichni dead, tak lvlcleared false
			lvlCleared = false;
		}
	}

	if (lvlCleared)
	{
		if (mPlayer->GetActice() == true)
			mCurrentState = finished;
	}
}

void Level::HandleEnemyPassed()
{
	for (int i = 0; i < mEnemies.size(); i++)
	{
		Vector2d pos = mEnemies[i]->GetPos();
		if (pos.y > Graphics::Instatnce()->SCREEN_HEIGHT)
		{
			mEnemies[i]->SetActive(false);
		}


	}



}


void Level::HandleStartLabel()
{
	mLabelTimer += mTimer->GetDeltaTime();
	if (mLabelTimer >= mLvlLabelOffScreen)
	{
		if (mCurStage > 1)
			StartLevel();
		else
		{
			if (mLabelTimer >= mLvlReadyOffScreen)
			{
				StartLevel();
				mPlayer->SetActive(true);
				mPlayer->IsVisible(true);

			}
		}
	}
}

void Level::HandleCollisions()
{
	if (!mPlayerHit)
	{

		if (mPlayer->WasHit())
		{
			mPlayBar->SetGameLives(mPlayer->GetLives());
			mPlayerHit = true;
			mPlayerRespawnTimer = 0.0f;
			mPlayer->SetActive(false);
		}

	}
}

void Level::HandlePlayerDeath()
{
	if (!mPlayer->IsAnimating())
	{
		if (mPlayer->GetLives() > 0)
		{
			if (mPlayerRespawnTimer == 0.0f)
				mPlayer->IsVisible(false);

			mPlayerRespawnTimer += mTimer->GetDeltaTime();
			if (mPlayerRespawnTimer >= mPlayerRespawnDelay)
			{

				mPlayer->SetActive(true);
				mPlayer->IsVisible(true);
				mPlayerHit = false;
			}
		}
		else
		{
			if (mGameOverTimer == 0.0f)
				mPlayer->IsVisible(false);

			mGameOverTimer += mTimer->GetDeltaTime();
			if (mGameOverTimer >= mGameOverDelay)
				mCurrentState = gameover;

		}
	}
}

bool Level::NextLVL()
{
	return true;
}

Level::LEVEL_STATES Level::GetState()
{
	return mCurrentState;
}

void Level::Update()
{
	if (!mLvlStarted)
		HandleStartLabel();
	else
	{
		HandleCollisions();
		HandleEnemyPassed();
		if (!mSpawningFinished)
			HandleEnemySpawning();
		HandleEnemyDiving();

		for (int i = 0; i < mEnemies.size(); i++)
		{
			mEnemies[i]->Update();
		}

		if (mPlayerHit)
		{
			HandlePlayerDeath();
		}
	}
}

void Level::Render()
{
	if (!mLvlStarted)
	{
		if (mLabelTimer > mLvlLabelOnScreen && mLabelTimer < mLvlLabelOffScreen)
		{
			mLvlLabel->Render();
			mLvlNum->Render();
		}

		if (mLabelTimer > mLvlReadyOnScreen && mLabelTimer < mLvlReadyOffScreen)
			mLvlReadyLabel->Render();
	}
	else
	{
		for (int i = 0; i < mEnemies.size(); i++)
		{
			mEnemies[i]->Render();
		}

		if (mPlayerHit)
		{
			if (mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
				mLvlReadyLabel->Render();

			if (mGameOverTimer >= mGameOverLabelOnScreen)
				mGameOverLabel->Render();
		}
	}
}
