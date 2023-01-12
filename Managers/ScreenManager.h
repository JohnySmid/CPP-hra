#pragma once
#include "../Entities/Screen/StartScreen.h"
#include "../Entities/Screen/PlayScreen.h"

class ScreenManager
{
public:
	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();
private:
	enum SCREENS
	{
		start,
		play
	};
	static ScreenManager* sInstance;
	InputManager* mInput;
	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;

	SCREENS mCurrentScreen;

	ScreenManager();
	~ScreenManager();




};