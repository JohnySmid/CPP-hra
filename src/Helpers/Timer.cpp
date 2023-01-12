#include "Timer.h"

Timer* Timer::sInstance = nullptr;

Timer* Timer::Instance()
{
	if (sInstance == nullptr)
		sInstance = new Timer();

	return sInstance;
}

void Timer::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

Timer::Timer()
{
	Reset();
	mElapsedTicks = 0;
	mDeltaTime = 0.0f;
	mTimeScale = 1.0f;
}

Timer::~Timer()
{

}

void Timer::Reset()
{
	mStartTicks = SDL_GetTicks();		//returns number of ms
}

float Timer::GetDeltaTime()
{
	return mDeltaTime;
}

void Timer::SetTimeScale(float t)
{
	mTimeScale = t;
}

float Timer::GetTimeScale()
{
	return mTimeScale;
}

void Timer::Update()
{
	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	mDeltaTime = mElapsedTicks * 0.001f;			//value in seconst
}