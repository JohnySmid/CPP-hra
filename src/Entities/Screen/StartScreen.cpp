#include "StartScreen.h"


StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mBgrd = new GameEntity(0.0f, 0.0f);
	mTopBar = new GameEntity(Graphics::Instatnce()->SCREEM_WIDTH * 0.5f, 80.0f);

	// --- Bgrnd ---
	mBackgroundTexture = new Texture("emr_camo.png");
	mLogo = new Texture("soldat.png");
	mPlay = new Texture("PLAY", "SEAS.ttf", 32, { 255, 100, 255 });
	mPressToPlay = new Texture("Press SPACE to play!", "SEAS.ttf", 20, { 180, 255, 255 });

	mTopBar->SetParent(this);
	mBackgroundTexture->SetParent(mBgrd);
	mLogo->SetParent(mTopBar);
	mPlay->SetParent(mTopBar);
	mPressToPlay->SetParent(mTopBar);

	mBackgroundTexture->SetPos(Vector2d(Graphics::Instatnce()->SCREEM_WIDTH * 0.5f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.5f));
	mLogo->SetPos(Vector2d(0.0f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.2f));
	mPlay->SetPos(Vector2d(0.0f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.5f));
	mPressToPlay->SetPos(Vector2d(0.0f, Graphics::Instatnce()->SCREEN_HEIGHT * 0.65f));

	ResetAnim();
}

StartScreen::~StartScreen()
{
	delete mBgrd;
	mBgrd = nullptr;
	delete mTopBar;
	mTopBar = nullptr;
	delete mBackgroundTexture;
	mBackgroundTexture = nullptr;
	delete mLogo;
	mLogo = nullptr;
	delete mPlay;
	mPlay = nullptr;
	delete mPressToPlay;
	mPressToPlay = nullptr;
}

void StartScreen::ResetAnim()
{
	PlayTheme();
	mAnimStartPos = Vector2d(0.0f, Graphics::Instatnce()->SCREEN_HEIGHT);
	mAnimEndPos = Vec2_ZERO;
	mAnimTotalTime = 3;
	mAnimTimer = 0.0f;
	mAnimDone = false;

	SetPos(mAnimStartPos);
}

void StartScreen::PlayTheme()
{
	mAudio->PlayMusic("startscreen.wav");
}

void StartScreen::StopTheme()
{
	mAudio->PauseMusic();
}

void StartScreen::Update()
{

	if (!mAnimDone)
	{
		mAnimTimer += mTimer->GetDeltaTime();
		SetPos(lerp(mAnimStartPos, mAnimEndPos, mAnimTimer / mAnimTotalTime));

		if (mAnimTimer >= mAnimTotalTime)
			mAnimDone = true;
	}
}

void StartScreen::Render()
{
	mBackgroundTexture->Render();
	mLogo->Render();
	mPlay->Render();
	mPressToPlay->Render();

}

