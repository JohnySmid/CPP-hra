#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animSpeed, ANIM_DIR animDir)
	: Texture(filename, x, y, w, h)
{
	mTimer = Timer::Instance();

	mStartX = x;
	mStartY = y;
	mFrameCount = frameCount;
	mAnimationSpeed = animSpeed;
	mTimePerFrame = animSpeed / frameCount;
	mAnimationTimer = 0.0f;

	mAnimationDirection = animDir;

	mAnimationDone = false;

	mWrapMode = loop;
}

AnimatedTexture::~AnimatedTexture()
{}

void AnimatedTexture::WrapMode(WRAP_MODE mode)
{
	mWrapMode = mode;
}

void AnimatedTexture::ResetAnimation()
{
	mAnimationTimer = 0.0f;
	mAnimationDone = false;
}

bool AnimatedTexture::IsAnimating()
{
	return (!mAnimationDone);
}

void AnimatedTexture::Update()
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->GetDeltaTime();	//time in seconds

		if (mAnimationTimer >= mAnimationSpeed)
		{
			if (mWrapMode == loop)
			{
				mAnimationTimer -= mAnimationSpeed;
			}
			else
			{
				mAnimationDone = true;
				mAnimationTimer = mAnimationSpeed - mTimePerFrame;	//step back one frame
			}
		}
		if (mAnimationDirection == horizontal)
		{
			mClip.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidht; //offset s mWidth
		}
		else
		{
			mClip.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
		}
	}
}