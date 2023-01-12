#include "PhyManager.h"


PhyManager* PhyManager::sInstance = nullptr;

PhyManager* PhyManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new PhyManager();

	return sInstance;
}

void PhyManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

void PhyManager::SetLayerCollMask(CollisionLayers layer, CollisionFlags flag)
{
	mLayerMasks[static_cast<unsigned int>(layer)] = std::bitset<static_cast<unsigned int>(CollisionLayers::MAXlayers)>(static_cast<unsigned int>(flag)); //kazdy layer ma svoji masku
}

unsigned long PhyManager::RegisterEntity(PhyEntity* entity, CollisionLayers layer)
{
	mCollisionLayers[static_cast<unsigned int>(layer)].push_back(entity);
	mLastId++;

	return mLastId;
}

void PhyManager::UnregisterEntity(unsigned long id)
{
	bool found = false;

	for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MAXlayers) && !found; i++)	// loop pres layers
	{
		for (int j = 0; j < mCollisionLayers[i].size() && !found; j++)							// loop pres vektory
		{
			if (mCollisionLayers[i][j]->GetId() == id)											//pokud najdeme
			{
				mCollisionLayers[i].erase(mCollisionLayers[i].begin() + j);
				found = true;																	//found = true pro exit loopu
			}
		}
	}
}

PhyManager::PhyManager()
{
	mLastId = 0;

	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MAXlayers); i++)
	{
		mLayerMasks[i] = std::bitset<static_cast<unsigned int>(CollisionLayers::MAXlayers)>(static_cast<unsigned int>(CollisionFlags::None));
	}
}

PhyManager::~PhyManager()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MAXlayers); i++)
	{
		mCollisionLayers[i].clear();
	}
}

void PhyManager::Update()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MAXlayers); i++)
	{
		//printf("i: %d\n", i);
		for (unsigned int j = 0; j < static_cast<unsigned int>(CollisionLayers::MAXlayers); j++)
		{
			//printf("i: %d, j: %d\n", i, j);
			// E B P -> 1x0x0
			if (mLayerMasks[i].test(j) && i <= j)
			{
				for (unsigned int k = 0; k < mCollisionLayers[i].size(); k++)
				{
					for (unsigned int l = 0; l < mCollisionLayers[j].size(); l++)
					{
						//printf("2. for\n");
						// Col det implementace
						if (mCollisionLayers[i][k]->CheckCollision(mCollisionLayers[j][l]))
						{
							mCollisionLayers[i][k]->Hit(mCollisionLayers[j][l]);
							mCollisionLayers[j][l]->Hit(mCollisionLayers[i][k]);
						}
					}
				}
			}
		}
	}

	//printf("kocka\n");
}