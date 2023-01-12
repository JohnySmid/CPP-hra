#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new ScreenManager();

	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager()
{
	mInput = InputManager::Instatnce();
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager()
{
	mInput = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;
	delete mPlayScreen;
	mPlayScreen = nullptr;
}

void ScreenManager::Update()
{

	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_SPACE))
		{
			mCurrentScreen = play;

			mPlayScreen->StartNewGame();
		}
		break;

	case play:
		mPlayScreen->Update();
		if (mPlayScreen->GameOver())
		{
			mCurrentScreen = start;
			mStartScreen->ResetAnim();
		}
		break;
	}
}

void ScreenManager::Render()
{
	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Render();
		break;
	case play:
		mPlayScreen->Render();
		break;
	}
}