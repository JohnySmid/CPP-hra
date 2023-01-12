#pragma once

#include "AudioManager.h"
#include "ScreenManager.h"
#include "PhyManager.h"


class GameManager
{
public:
	static GameManager* Instance();
	static void Release();

	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();

	void Run();

private:
	static GameManager* sInstance;
	bool mQuit;
	const int mFramerate = 60;

	AssetManager* mAssetManager;
	InputManager* mInputManager;
	AudioManager* mAudioManager;
	ScreenManager* mScreenManager;
	PhyManager* mPhyManager;


	Graphics* mGraphics;
	SDL_Event mEvents;
	Timer* mTimer;




	GameManager();
	~GameManager();
};