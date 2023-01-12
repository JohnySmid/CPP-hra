#include "PlayBar.h"

PlayBar::PlayBar()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mBackground = new Texture("bar_bgr.png");
	mScore = new ScoreBoard();


	// --- Bgrnd ---
	mBackground->SetParent(this);
	mBackground->SetPos(Vector2d(450.0f, 50.0f));
	mBackground->SetScale(Vector2d(2.0f, 10.0f));


	// --- Score ---
	mScoreL = new Texture("SCORE", "SEAS.ttf", 20, { 150,0,0 });
	mScoreL->SetParent(this);
	mScoreL->SetPos(Vector2d(400.0f, -410.0f));

	mScore->SetParent(this);
	mScore->SetPos(Vector2d(430.0f, -370.0f));


	// --- HP ---
	mNumHp = new Texture("Health", "SEAS.ttf", 20, { 150,0,0 });
	mNumHp->SetParent(this);
	mNumHp->SetPos(Vector2d(410.0f, -320.0f));

	mHp = new GameEntity();
	mHp->SetParent(this);
	mHp->SetPos(Vector2d(400.0f, -270.0f));

	for (int i = 0; i < HPtotal; i++)
	{
		mHPtxt[i] = new Texture("hptxt.png");
		mHPtxt[i]->SetParent(mHp);
		mHPtxt[i]->SetPos(Vector2d(35.0f * i, 0.0f));
	}


	// --- Level ---
	mNumLevel = new Texture("LEVEL", "SEAS.ttf", 20, { 150,0,0 });
	mNumLevel->SetParent(this);
	mNumLevel->SetPos(Vector2d(400.0f, -230.0f));

	mLVL = new GameEntity();
	mLVL->SetParent(this);
	mLVL->SetPos(Vector2d(435.0f, -180.0f));

	RenderedLvl = false;

	// --- Timer ---
	mLvlTimer = 0.0f;
	mLvlInterval = 0.5f;
}

PlayBar::~PlayBar()
{
	mTimer = nullptr;
	mAudio = nullptr;
	delete mScore;
	mScore = nullptr;
	delete mBackground;
	mBackground = nullptr;
	delete mScoreL;
	mScoreL = nullptr;
	delete mNumHp;
	mNumHp = nullptr;
	delete mHp;
	mHp = nullptr;
	for (int i = 0; i < HPtotal; i++)
	{
		delete mHPtxt[i];
		mHPtxt[i] = nullptr;
	}
	delete mNumLevel;
	mNumLevel = nullptr;
	delete mLVL;
	mLVL = nullptr;
	delete mLVLtxt;
	mLVLtxt = nullptr;
}


void PlayBar::SetGameScore(int score)
{
	mScore->SetScore(score);
}

void PlayBar::SetGameLives(int lives)
{
	mHpRest = lives;
}
void PlayBar::ClearVektor()
{
	for (int i = 0; i < mLVLtxtvektor.size(); i++)
	{
		delete mLVLtxtvektor[i];
		mLVLtxtvektor[i] = nullptr;
	}
	mLVLtxtvektor.clear();
}

void PlayBar::SetGameLvl(int lvl)
{
	ClearVektor();
	if (lvl >= 4)
		mMaxLvl = 3;
	else
		mMaxLvl = lvl;
}

void PlayBar::Levels()
{
	if (mMaxLvl >= 3)
		RenderLVL("lvl3.png", 3);
	else if (mMaxLvl >= 2)
		RenderLVL("lvl2.png", 2);
	else if (mMaxLvl >= 1)
		RenderLVL("lvl1.png", 1);
	else
		RenderLVL("lvl0.png", 0);
}

void PlayBar::RenderLVL(std::string filename, int lvl)
{
	int index = mLVLtxtvektor.size();

	mMaxLvl -= lvl;
	mLVLtxtvektor.push_back(new Texture(filename));
	mLVLtxtvektor[index]->SetParent(mLVL);
	mLVLtxtvektor[index]->SetPos(Vec2_RIGHT);

	mAudio->PlaySFX("lvlgoesup.wav");

}


void PlayBar::Update()
{
	if (mMaxLvl > 0)
	{
		mLvlTimer += mTimer->GetDeltaTime();
		if (mLvlTimer >= mLvlInterval)
		{
			Levels();
			mLvlTimer = 0.0f;
		}
	}
}

void PlayBar::Render()
{
	mBackground->Render();

	mScore->Render();

	mScoreL->Render();

	mNumHp->Render();

	for (int i = 0; i < HPtotal && i < mHpRest; i++)
	{
		mHPtxt[i]->Render();
	}

	mNumLevel->Render();

	for (int i = 0; i < mLVLtxtvektor.size(); i++)
	{
		mLVLtxtvektor[i]->Render();
	}
}
