#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <stdio.h>

class Graphics
{
public:
	static const int SCREEM_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 896;
	const char* TITLE = "des. Smid";

	SDL_Texture* loadTexture(std::string path);
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);	//ttf funguje: dame string a to nam vrati texture* na vyrenderovany text

	static Graphics* Instatnce();
	static void Release();
	static bool Initialized();

	void ClearBackBuffer();

	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = nullptr, SDL_Rect* rend = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void Render();

private:
	static Graphics* sInstance;
	static bool sInitialize;
	static bool is_Initialized;

	SDL_Window* mWindow;
	SDL_Surface* mBackbuffer;
	SDL_Renderer* mRenderer;

	Graphics();
	~Graphics();
	bool Init();
};