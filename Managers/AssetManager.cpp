#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager* AssetManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new AssetManager();

	return sInstance;
}

void AssetManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

AssetManager::AssetManager()
{}

AssetManager::~AssetManager()
{
	for (auto tex : mTextures)
	{
		if (tex.second != NULL)
		{
			SDL_DestroyTexture(tex.second);
		}
	}
	mTextures.clear();

	for (auto text : mText)
	{
		if (text.second != NULL)
		{
			SDL_DestroyTexture(text.second);
		}
	}
	mText.clear();

	for (auto font : mFonts)
	{
		if (font.second != NULL)
		{
			TTF_CloseFont(font.second);
		}
	}
	mFonts.clear();

	for (auto music : mMusic)
	{
		if (music.second != NULL)
		{
			Mix_FreeMusic(music.second);
		}
	}
	mMusic.clear();

	for (auto sfx : mSFX)
	{
		if (sfx.second != NULL)
		{
			Mix_FreeChunk(sfx.second);
		}
	}
	mSFX.clear();
}

SDL_Texture* AssetManager::GetTexture(std::string filename)
{
	std::string fullpath = "assets/txt/";
	fullpath.append(filename);

	if (mTextures[fullpath] == nullptr)
		mTextures[fullpath] = Graphics::Instatnce()->loadTexture(fullpath);

	return mTextures[fullpath];
}

TTF_Font* AssetManager::GetFont(std::string filename, int size)
{
	std::string fullpath = "assets/fonts/";
	fullpath.append(filename);
	std::string key = fullpath + (char)size;

	if (mFonts[key] == nullptr)
	{
		mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);
		if (mFonts[key] == nullptr)
			printf("AM: Font load error: %s - %s", filename.c_str(), TTF_GetError());

	}

	return mFonts[key];
}

SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color)
{
	TTF_Font* font = GetFont(filename, size);

	std::string key = text + filename + (char)size + (char)color.r + (char)color.g + (char)color.b;

	if (mText[key] == nullptr)
		mText[key] = Graphics::Instatnce()->CreateTextTexture(font, text, color);

	return mText[key];
}

Mix_Music* AssetManager::GetMusic(std::string filename)
{
	std::string fullpath = "assets/sounds/";
	fullpath.append(filename);

	if (mMusic[fullpath] == nullptr)
	{
		mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());

		if (mMusic[fullpath] == nullptr)
			printf("AM: Music load error: %s - %s", filename.c_str(), Mix_GetError());
	}

	return mMusic[fullpath];
}

Mix_Chunk* AssetManager::GetSFX(std::string filename)
{
	std::string fullpath = "assets/sounds/";
	fullpath.append(filename);

	if (mSFX[fullpath] == nullptr)
	{
		mSFX[fullpath] = Mix_LoadWAV(fullpath.c_str());

		if (mSFX[fullpath] == nullptr)
			printf("AM: SFX load error: %s - %s", filename.c_str(), Mix_GetError());
	}

	return mSFX[fullpath];
}