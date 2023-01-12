#pragma once
#include "../Textures/AnimatedTexture.h"
#include "ScoreBoard.h"
#include "../../Managers/InputManager.h"
#include "../../Managers/AudioManager.h"



class StartScreen : public GameEntity
{
public:
	StartScreen();
	~StartScreen();

	void ResetAnim();
	void PlayTheme();
	void StopTheme();

	void Update();
	void Render();
private:
	//topbar ent.
	GameEntity* mTopBar;
	GameEntity* mBgrd;
	AudioManager* mAudio;
	ScoreBoard* mHighestScore;


	Texture* mBackgroundTexture;
	Texture* mHighScore;
	Texture* mLogo;
	Texture* mPlay;
	Texture* mPressToPlay;

	Timer* mTimer;

	Vector2d mAnimStartPos;
	Vector2d mAnimEndPos;
	float mAnimTotalTime;
	float mAnimTimer;
	bool mAnimDone;
};

