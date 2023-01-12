#include "AudioManager.h"

AudioManager* AudioManager::sInstance = nullptr;
AudioManager* AudioManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new AudioManager();

	return sInstance;
}

void AudioManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

AudioManager::AudioManager()
{
	mAssetManager = AssetManager::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		printf("Mixer init Error: %s", Mix_GetError());
}

AudioManager::~AudioManager()
{
	mAssetManager = nullptr;
	Mix_Quit();
}

void AudioManager::PlayMusic(std::string filename, int loop)
{
	Mix_PlayMusic(mAssetManager->GetMusic(filename), loop); //Mix_Music*, loop = 0 1x, loop -1 looping

}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic;
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic;
}

void AudioManager::PlaySFX(std::string filename, int loop, int channel)
{
	Mix_PlayChannel(channel, mAssetManager->GetSFX(filename), loop);
}