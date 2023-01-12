#pragma once
#include "GameEntity.h"
#include "Screen/PlayBar.h"
#include "Player.h"
#include "Bad.h"

class Level : public GameEntity
{
public:
	enum LEVEL_STATES
	{
		running,
		finished,
		gameover
	};

	Level(int lvl, PlayBar* playBar, Player* player);
	~Level();

	bool NextLVL();

	LEVEL_STATES GetState();



	void Update();
	void Render();
private:
	Timer* mTimer;
	InputManager* mInput;

	PlayBar* mPlayBar;
	Player* mPlayer;
	Enemy* mEnemy;

	int mBadCount;
	static int mBadLimit;
	const int mBadPlus = 5;
	std::vector<Enemy*> mEnemies;

	LEVEL_STATES mCurrentState;

	bool mPlayerHit;
	float mPlayerRespawnDelay;
	float mPlayerRespawnTimer;
	float mPlayerRespawnLabelOnScreen;

	int mCurStage;
	bool mLvlStarted;

	float mLabelTimer;

	Texture* mLvlLabel;
	ScoreBoard* mLvlNum;
	float mLvlLabelOnScreen;		//in point, kde se zobrazi
	float mLvlLabelOffScreen;		//off point, kde zmizí

	Texture* mLvlReadyLabel;
	float mLvlReadyOnScreen;
	float mLvlReadyOffScreen;

	void StartLevel();
	void HandleStartLabel();
	void HandleCollisions();
	void HandlePlayerDeath();

	void HandleEnemySpawning();
	void HandleEnemyDiving();
	void HandleEnemyPassed();

	bool mSpawningFinished;
	float mSpawnDelay;
	float mSpawnTimer;


	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;
};