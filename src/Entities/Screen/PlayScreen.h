#pragma once
#include "../Level.h"

class PlayScreen : public GameEntity
{
public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	bool GameOver();

	void Update();
	void Render();

private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	PlayBar* mPlayBar;
	Level* mLevel;
	Player* mPlayer;

	Texture* mStartLabel;
	float mLvlStartTimer;
	float mLvlStartDelay;
	float mLvlTimer;
	bool mGameStarted;

	bool mLvlStarted;
	int mCurrentLvl;


	void NextLvl();
};

