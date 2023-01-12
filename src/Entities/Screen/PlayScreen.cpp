#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instatnce();
	mAudio = AudioManager::Instance();


	// --- Playbar ---
	mPlayBar = new PlayBar();
	mPlayBar->SetParent(this);
	mPlayBar->SetPos(Vector2d(Graphics::Instatnce()->SCREEM_WIDTH * 0.5f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.5f)); //centr okna


	// --- Starting label ---
	mStartLabel = new Texture("START", "SEAS.ttf", 32, { 150,0,0 });
	mStartLabel->SetParent(this);
	mStartLabel->SetPos(Vector2d(Graphics::Instatnce()->SCREEM_WIDTH * 0.425f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.5f));


	// --- Level ---
	mLevel = nullptr;

	mLvlStartDelay = 1.0f; //1s delay mezi lvl
	mLvlStarted = false;


	// --- Player ---
	mPlayer = nullptr;

}

PlayScreen::~PlayScreen()
{
	mTimer = nullptr;
	mInput = nullptr;
	delete mPlayBar;
	mPlayBar = nullptr;
	delete mStartLabel;
	mStartLabel = nullptr;
	delete mLevel;
	mLevel = nullptr;
	delete mPlayer;
	mPlayer = nullptr;
}

void PlayScreen::NextLvl()
{
	mCurrentLvl++;
	mLvlStartTimer = 0.0f;
	mLvlStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentLvl, mPlayBar, mPlayer);
}

void PlayScreen::StartNewGame()
{
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->SetParent(this);
	mPlayer->SetPos(Vector2d(Graphics::Instatnce()->SCREEM_WIDTH * 0.425f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.85f));
	mPlayer->SetActive(false);

	mPlayBar->SetGameScore(mPlayer->GetScore());
	mPlayBar->SetGameLives(mPlayer->GetLives());
	mPlayBar->SetGameLvl(0);

	mGameStarted = false;
	mLvlStarted = false;
	mLvlStartTimer = 0.0f;
	mCurrentLvl = 0;

	mAudio->PlayMusic("lvltheme.wav");
}

bool PlayScreen::GameOver()
{
	if (!mLvlStarted)
		return false;

	return (mLevel->GetState() == Level::gameover);
}

void PlayScreen::Update()
{
	if (mGameStarted)
	{
		if (!mLvlStarted)
		{
			mLvlStartTimer += mTimer->GetDeltaTime();
			if (mLvlStartTimer >= mLvlStartDelay)
				NextLvl();
		}
	}
	else
	{
		mLvlTimer += mTimer->GetDeltaTime();
		if (mLvlTimer >= mLvlStartDelay)
		{
			mGameStarted = true;
			//printf("game started");
		}
	}

	if (mGameStarted)
	{
		if (mCurrentLvl > 0)
			mPlayBar->Update();
		if (mLvlStarted)
		{
			mLevel->Update();

			if (mLevel->GetState() == Level::finished)
			{
				mLvlStarted = false;
			}
		}
		mPlayer->Update();
		mPlayBar->SetGameScore(mPlayer->GetScore());
	}
}

void PlayScreen::Render()
{
	mPlayBar->Render();

	if (!mGameStarted)
	{
		mStartLabel->Render();
		//printf("\nloading");
	}

	if (mGameStarted)
	{
		if (mLvlStarted)
			mLevel->Render();
		//printf("\nstart lvl");

		mPlayer->Render();
	}
}