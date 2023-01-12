#pragma once
#include "../GameEntity.h"
#include "../../Managers/AssetManager.h"

class Texture : public GameEntity
{
public:
	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int w, int h);
	Texture(std::string filename, std::string fontpath, int size, SDL_Color color);
	~Texture();

	Vector2d ScaleDim();

	virtual void Render();			//chceme inherit, proto virtual


protected:
	SDL_Texture* mTex;
	Graphics* mGraphics;
	SDL_Rect mRenderRect;
	SDL_Rect mClip;

	int mWidht;
	int mHeight;
	bool mIs_clipped;
};

