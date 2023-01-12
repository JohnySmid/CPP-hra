#include "Texture.h"


Texture::Texture(std::string filename)
{
	mGraphics = Graphics::Instatnce();
	mTex = AssetManager::Instance()->GetTexture(filename);

	SDL_QueryTexture(mTex, NULL, NULL, &mWidht, &mHeight);			//save W a H texture

	mIs_clipped = false;
	mRenderRect.w = mWidht;
	mRenderRect.h = mHeight;

}

Texture::Texture(std::string filename, int x, int y, int w, int h)
{
	mGraphics = Graphics::Instatnce();
	mTex = AssetManager::Instance()->GetTexture(filename);

	mIs_clipped = true;

	mWidht = w;
	mHeight = h;
	mRenderRect.w = mWidht;
	mRenderRect.h = mHeight;

	mClip.x = x;
	mClip.y = y;
	mClip.w = mWidht;
	mClip.h = mHeight;
}

Texture::Texture(std::string text, std::string fontpath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instatnce();
	mTex = AssetManager::Instance()->GetText(text, fontpath, size, color);

	SDL_QueryTexture(mTex, NULL, NULL, &mWidht, &mHeight);


	mIs_clipped = false;
	mRenderRect.w = mWidht;
	mRenderRect.h = mHeight;
}


Texture::~Texture()
{
	mTex = nullptr;
	mGraphics = nullptr;
}
Vector2d Texture::ScaleDim()
{
	Vector2d scaleDim = GetScale();
	scaleDim.x *= mWidht;
	scaleDim.y *= mHeight;

	return scaleDim;
}

void Texture::Render()
{
	Vector2d pos = GetPos(world);
	Vector2d scale = GetScale(world);

	mRenderRect.x = (int)(pos.x - mWidht * scale.x * 0.5f);
	mRenderRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
	mRenderRect.w = (int)(mWidht * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);

	if (mIs_clipped)
		mGraphics->DrawTexture(mTex, &mClip, &mRenderRect);
	else
		mGraphics->DrawTexture(mTex, nullptr, &mRenderRect, GetRotation(world));
	//reference na rend!!!
}