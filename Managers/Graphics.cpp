#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;
bool Graphics::sInitialize = false;


Graphics* Graphics::Instatnce()
{
	if (sInstance == nullptr)
		sInstance = new Graphics();

	return sInstance;
}

void Graphics::Release()
{
	delete sInstance;
	sInstance = nullptr;

	sInitialize = false;

}


bool Graphics::Initialized()
{
	return sInitialize;
}


Graphics::Graphics()
{
	mBackbuffer = NULL;

	sInitialize = Init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}


bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL Init error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		mWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEM_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow == NULL)
		{
			printf("Window Error: %s\n", SDL_GetError());
			return false;
		}


		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

		if (mRenderer == nullptr)
		{
			printf("Renderer Error: %s\n", SDL_GetError());
			return false;
		}

		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags))
		{
			printf("Error IMG init: %s\n", IMG_GetError());
			return false;
		}

		if (TTF_Init() == -1)
		{
			printf("Error TTF init: %s\n", TTF_GetError());
			return false;
		}

		mBackbuffer = SDL_GetWindowSurface(mWindow);
		return true;
	}


}

void Graphics::Render()
{
	SDL_RenderPresent(mRenderer);
}

SDL_Texture* Graphics::loadTexture(std::string path)
{
	SDL_Texture* tex = nullptr;

	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == NULL)
	{
		printf("Image load Error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
		return tex;
	}

	tex = SDL_CreateTextureFromSurface(mRenderer, surface);

	if (tex == nullptr)
	{
		printf("Texture Error: %s\n", SDL_GetError());
		return tex;
	}
	SDL_FreeSurface(surface);

	return tex;
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (surface == NULL)
	{
		printf("TTF load Error: %s", TTF_GetError());
		return nullptr;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);

	if (tex == NULL)
	{
		printf("Text texture Error: %s\n", SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(surface);

	return tex;
}


void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, NULL, flip);
}