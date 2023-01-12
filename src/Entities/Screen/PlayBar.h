#pragma once
#include "../../Helpers/Timer.h"
#include "ScoreBoard.h"
#include "../../Managers/AudioManager.h"



class PlayBar : public GameEntity
{
public:
	PlayBar();
	~PlayBar();

	void SetGameScore(int score);
	void SetGameLives(int lives);
	void SetGameLvl(int lvl);

	void Update();
	void Render();

private:
	Timer* mTimer;
	AudioManager* mAudio;
	ScoreBoard* mScore;


	Texture* mBackground;
	Texture* mScoreL;
	Texture* mNumHp;
	Texture* mNumLevel;

	static const int HPtotal = 3;		//pevne dane zivoty pro for render
	int mHpRest;						// zivoty zbyvaji
	GameEntity* mHp;
	Texture* mHPtxt[HPtotal];

	GameEntity* mLVL;
	Texture* mLVLtxt;
	std::vector<Texture*> mLVLtxtvektor;
	int mMaxLvl;
	bool RenderedLvl;
	float mLvlTimer;
	float mLvlInterval;

	void RenderLVL(std::string filename, int lvl);
	void Levels();
	void ClearVektor();

};

