#pragma once
#include "../Entities/PhyEntity.h"
#include <bitset>

class PhyManager
{
public:
	enum class CollisionLayers
	{
		Player = 0,
		PlayerBullets,
		Enemy,
		//////////////////
		MAXlayers
	};

	enum class CollisionFlags
	{
		None = 0x00,
		Player = 0x01,
		PlayerBullets = 0x02,
		Enemy = 0x04
	};

	static PhyManager* Instance();
	static void Release();

	void SetLayerCollMask(CollisionLayers layer, CollisionFlags flag);
	unsigned long RegisterEntity(PhyEntity* entity, CollisionLayers layer);
	void UnregisterEntity(unsigned long id);

	void Update();

private:
	static PhyManager* sInstance;
	PhyManager();
	~PhyManager();

	std::vector<PhyEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MAXlayers)]; // kazdy item arraye bude mít svùj vektor
	std::bitset<static_cast<unsigned int>(CollisionLayers::MAXlayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MAXlayers)];

	unsigned long mLastId;
};


inline PhyManager::CollisionFlags operator|(PhyManager::CollisionFlags a, PhyManager::CollisionFlags b)
{
	return static_cast<PhyManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhyManager::CollisionFlags operator&(PhyManager::CollisionFlags a, PhyManager::CollisionFlags b)
{
	return static_cast<PhyManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}