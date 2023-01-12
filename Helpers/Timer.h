#pragma once
#include <SDL.h>

class Timer
{
public:
	static Timer* Instance();
	static void Release();

	void Reset();
	void Update();

	float GetDeltaTime();

	void SetTimeScale(float t);
	float GetTimeScale();

private:
	static Timer* sInstance;
	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;

	Timer();
	~Timer();
};