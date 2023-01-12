#include "GameManager.h"

GameManager* GameManager::sInstance = nullptr;

GameManager* GameManager::Instance() {
	if (sInstance == nullptr)
		sInstance = new GameManager();

	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

GameManager::GameManager()
{
	mQuit = false;

	mGraphics = Graphics::Instatnce();

	//pokud chyba exit loop
	if (!Graphics::Initialized())
		mQuit = true;

	//Instance všech manažerù + kolize
	mTimer = Timer::Instance();
	mAssetManager = AssetManager::Instance();
	mAudioManager = AudioManager::Instance();
	mInputManager = InputManager::Instatnce();
	mPhyManager = PhyManager::Instance();
	mPhyManager->SetLayerCollMask(PhyManager::CollisionLayers::Player, PhyManager::CollisionFlags::Enemy);
	mPhyManager->SetLayerCollMask(PhyManager::CollisionLayers::PlayerBullets, PhyManager::CollisionFlags::Enemy);
	mPhyManager->SetLayerCollMask(PhyManager::CollisionLayers::Enemy, PhyManager::CollisionFlags::PlayerBullets); //PhyManager::CollisionFlags::Player |


	mScreenManager = ScreenManager::Instance();

}

GameManager::~GameManager()
{
	//Asset musi byt 1., kvuli SDL releasovani
	AssetManager::Release();
	mAssetManager = nullptr;
	/* ------------------------------------------- */
	ScreenManager::Release();
	mScreenManager = nullptr;

	PhyManager::Release();
	mPhyManager = nullptr;

	Graphics::Release();
	mGraphics = nullptr;

	Timer::Release();
	mTimer = nullptr;

	AudioManager::Release();
	mAudioManager = nullptr;

	InputManager::Release();
	mInputManager = nullptr;

}

void GameManager::EarlyUpdate()
{
	mInputManager->Update();
}

void GameManager::Update()
{
	mScreenManager->Update();
}

void GameManager::Render()
{
	mGraphics->ClearBackBuffer();

	//Draw calls
	mScreenManager->Render();


	mGraphics->Render();
}

void GameManager::LateUpdate()
{
	//kolize = PhyManager
	mPhyManager->Update();
	mInputManager->UpdatePrevInput();
	mTimer->Reset();
}

void GameManager::Run()
{
	while (!mQuit)
	{
		mTimer->Update(); //update timer na zacatku kazdeho loop

		while (SDL_PollEvent(&mEvents) != 0)
		{
			if (mEvents.type == SDL_QUIT)
			{
				mQuit = true;
			}
		}

		//Timer
		if (mTimer->GetDeltaTime() >= 1.0f / mFramerate)
		{
			EarlyUpdate();
			Update();
			LateUpdate();		//col detection, fyzika
			Render();
		}

	}
}