#pragma once
#include "../../Helpers/Timer.h"
#include "Texture.h"

class AnimatedTexture : public Texture
{
public:
	enum WRAP_MODE
	{
		once = 0,
		loop
	};
	enum ANIM_DIR
	{
		horizontal = 0,
		vertical
	};

	AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animSpeed, ANIM_DIR animDir);
	~AnimatedTexture();

	void WrapMode(WRAP_MODE mode);
	void ResetAnimation();
	bool IsAnimating();

	void Update();				//vyuzivame z public Texture virtual void Render

private:
	Timer* mTimer;
	int mStartX;
	int mStartY;

	float mAnimationTimer;		//track time
	float mAnimationSpeed;		//total time of anim
	float mTimePerFrame;		//time for how long in frames
	int mFrameCount;			//how much of anim pict

	WRAP_MODE mWrapMode;
	ANIM_DIR mAnimationDirection;

	bool mAnimationDone;
};

